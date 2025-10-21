#include <qdebug.h>
#include <random>
#include <algorithm>

#include "kanjiquiz.h"
#include "network/apiconnectionclass.h"

KanjiQuiz::KanjiQuiz(QObject *parent)
{
    qDebug()<<"kanji quiz constructor";
}

void KanjiQuiz::setEnglishNameTxt(QString newVal)
{
    m_englishNameTxt = newVal;
}

void KanjiQuiz::setKanjiTxt(QString newVal)
{
    m_kanjiTxt = newVal;
}

void KanjiQuiz::setKunyomiTxt(QString newVal)
{
    m_kunyomiTxt = newVal;
}

void KanjiQuiz::setOnyomiTxt(QString newVal)
{
    m_onyomiTxt = newVal;
}

void KanjiQuiz::getKanjiList(QList<KanjiListStruct> list)
{
    kanjiList = list;
    qDebug()<<"getKanjiList"<<kanjiList.count();

    //reset counter whenever user returns to main menu
    currentListIndex = 0;
    randomizeKanjiList();
}

void KanjiQuiz::randomizeKanjiList()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    //initial values for labels in qml
    if(!kanjiList.empty())
    {
        std::shuffle(kanjiList.begin(), kanjiList.end(), gen);

        setItemsVal();
    }
}

void KanjiQuiz::getNextItem()
{
    if(checkIfStringMatches(m_kunyomiTxt, kanjiList.at(currentListIndex).kunyomi) &&
        checkIfStringMatches(m_onyomiTxt, kanjiList.at(currentListIndex).onyomi))
    {
        if(currentListIndex < kanjiList.count())
        {

            QDate nextDate = getDaysToAddToItem(currentListIndex);
            int currentCorrectCounter = kanjiList.at(currentListIndex).correctStreak;

            kanjiQuizItemList.append({
                kanjiList.at(currentListIndex).kanjiId,
                true,
                QDate::currentDate(),
                nextDate,
                ++currentCorrectCounter,
                kanjiList.at(currentListIndex).kanji,
                kanjiList.at(currentListIndex).onyomi,
                kanjiList.at(currentListIndex).kunyomi,
                kanjiList.at(currentListIndex).kanjiEnglishName

            });

            kanjiListToUpdate.append({
                kanjiList.at(currentListIndex).kanjiId,
                kanjiList.at(currentListIndex).kanji,
                kanjiList.at(currentListIndex).onyomi,
                kanjiList.at(currentListIndex).kunyomi,
                kanjiList.at(currentListIndex).kanjiEnglishName,
                QDate::currentDate().toString("yyyy-MM-dd"),
                nextDate.toString("yyyy-MM-dd"),
                ++currentCorrectCounter,
                true
            });

            if(currentListIndex < kanjiList.count() -1)
            {
                currentListIndex++;
                setItemsVal();
            }
            else
            {
                std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
                apiConnClass->UpdateKanjiDbItemsForUser(kanjiQuizItemList);

                QEventLoop loop;
                connect(apiConnClass.get(), &ApiConnectionClass::updateKanjiDateFinished, &loop, &QEventLoop::quit);
                connect(apiConnClass.get(), &ApiConnectionClass::updateKanjiDateFinished,this, [&](){
                    emit quizFinished();
                });

                loop.exec();
            }
        }
        emit getNextItemTriggered();
    }
}

void KanjiQuiz::skipItem()
{
    qDebug()<<"skipped Item";

    //resets correct ctr and moves the item for the next day
    if(currentListIndex < kanjiList.count())
    {
        QDate nextDate = QDate::currentDate().addDays(1);
        int currentCorrectCounter = 0;

        kanjiQuizItemList.append({
            kanjiList.at(currentListIndex).kanjiId,
            false,
            QDate::currentDate(),
            nextDate,
            currentCorrectCounter,
            kanjiList.at(currentListIndex).kanji,
            kanjiList.at(currentListIndex).onyomi,
            kanjiList.at(currentListIndex).kunyomi,
            kanjiList.at(currentListIndex).kanjiEnglishName
        });

        kanjiListToUpdate.append({
            kanjiList.at(currentListIndex).kanjiId,
            kanjiList.at(currentListIndex).kanji,
            kanjiList.at(currentListIndex).onyomi,
            kanjiList.at(currentListIndex).kunyomi,
            kanjiList.at(currentListIndex).kanjiEnglishName,
            QDate::currentDate().toString("yyyy-MM-dd"),
            nextDate.toString("yyyy-MM-dd"),
            currentCorrectCounter,
            true
        });

        if(currentListIndex < kanjiList.count() -1)
        {
            currentListIndex++;
            setItemsVal();
        }
        else
        {
            //dbConnClass->UpdateDbItems(kanjiQuizItemList, userId);
            std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
            apiConnClass->UpdateKanjiDbItemsForUser(kanjiQuizItemList);

            QEventLoop loop;
            connect(apiConnClass.get(), &ApiConnectionClass::updateKanjiDateFinished, &loop, &QEventLoop::quit);
            connect(apiConnClass.get(), &ApiConnectionClass::updateKanjiDateFinished,this, [&](){
                emit quizFinished();
            });

            loop.exec();
        }
        emit getNextItemTriggered();
    }
}

void KanjiQuiz::clearQuizList()
{
    kanjiQuizItemList.clear();
}

QString KanjiQuiz::getCorrectScore()
{
    int correctCtr = 0;
    for(KanjiQuizStruct &item :kanjiQuizItemList)
    {
        if(item.correctCounter != 0)
            ++correctCtr;
    }
    return QString::number(correctCtr);
}

QString KanjiQuiz::getIncorrectScore()
{
    int inCorrectCtr = 0;
    for(KanjiQuizStruct &item :kanjiQuizItemList)
    {
        if(item.correctCounter == 0)
            ++inCorrectCtr;
    }
    return QString::number(inCorrectCtr);
}

void KanjiQuiz::setItemsVal()
{
    m_englishNameTxt = kanjiList.at(currentListIndex).kanjiEnglishName;
    emit englishNameTxtChanged();

    m_kanjiTxt = kanjiList.at(currentListIndex).kanji;
    emit kanjiTxtChanged();
}

bool KanjiQuiz::checkIfStringMatches(QString txtVal, QString valToCompare)
{
    QString txt = txtVal;

    QStringList newStringList = getValStringList(txt);
    QStringList newCompareList = getValStringList(valToCompare);

    int correctCounter = 0;
    if(newStringList.empty())
        return false;

    for(int i = 0; i < newStringList.count(); i++)
    {
        for (int j = 0; j < newCompareList.count(); ++j)
        {
            if(newStringList[i] == newCompareList[j])
                correctCounter++;

        }
    }

    if(correctCounter > 0 && correctCounter < newCompareList.count())
    {
        qDebug()<<"you got some of it";
        return true;
    }
    if(correctCounter == newCompareList.count())
    {
        qDebug()<<"everything is correct";
        return true;
    }
    return false;
}

QStringList KanjiQuiz::getValStringList(QString val)
{
    QString kunyomiString = val;
    kunyomiString = kunyomiString.simplified();
    kunyomiString.replace(',',' ');

    //for JP comma
    int indexJpComma = kunyomiString.indexOf("、");
    kunyomiString = kunyomiString.replace(indexJpComma, 1, " ");
    //for JP hypen
    int indexJpHypen = kunyomiString.indexOf("ー");
    kunyomiString = kunyomiString.replace(indexJpHypen, 1, " ");

    QStringList stringList = kunyomiString.split(" ",Qt::SkipEmptyParts);

    return stringList;
}

QDate KanjiQuiz::getDaysToAddToItem(int index)
{
    int correctCtr = kanjiList.at(index).correctStreak;
    QDate currentDate = QDate::currentDate();
    QDate nextDate;
    if(correctCtr < 3)
        nextDate = currentDate.addDays(1);
    if (correctCtr >= 3 && correctCtr << 6)
        nextDate = currentDate.addDays(3);
    if (correctCtr >= 6 && correctCtr << 9)
        nextDate = currentDate.addDays(7);
    if (correctCtr >= 9 && correctCtr << 12)
        nextDate = currentDate.addMonths(1);
    if (correctCtr > 12)
        nextDate = currentDate.addYears(500);

    return nextDate;
}

