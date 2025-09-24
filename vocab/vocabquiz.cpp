#include "vocabquiz.h"
#include <random>
#include <algorithm>
#include "dbconnectionclass.h"

VocabQuiz::VocabQuiz(QObject *parent)
{
    qDebug()<<"vocab quiz constructor";
    dbConnClass = new DbConnectionClass;
    xmlReader = new XMLReaderClass;

    //get user id
    xmlReader->loadDocument("Config.xml");
    userId = xmlReader->getSavedUserInfo().at(0);
}

void VocabQuiz::setVocabMeaningTxt(QString newVal)
{
    m_vocabMeaningTxt = newVal;
}

void VocabQuiz::setVocabKanjiTxt(QString newVal)
{
    m_vocabKanjiTxt = newVal;
}

void VocabQuiz::setVocabReadingTxt(QString newVal)
{
    m_vocabReadingTxt = newVal;
}

void VocabQuiz::getVocabList(QList<VocabListStruct> list)
{
    vocabList = list;

    //reset counter whenever user returns to main menu
    currentListIndex = 0;
    randomizeVocabList();
}

QString VocabQuiz::getNextItem()
{
    qDebug()<<"vocablist.reading: "<<vocabList.at(currentListIndex).vocabReading;
    qDebug()<<"textfield reading: "<<m_vocabReadingTxt;
    if(checkIfStringMatches(m_vocabReadingTxt, vocabList.at(currentListIndex).vocabReading))
    {
        if(currentListIndex < vocabList.count())
        {

            QDate nextDate = getDaysToAddToItem(currentListIndex);
            int currentCorrectCounter = vocabList.at(currentListIndex).correctStreak;

            vocabQuizItemList.append({
                vocabList.at(currentListIndex).vocabId,
                true,
                QDate::currentDate(),
                nextDate,
                ++currentCorrectCounter,
                vocabList.at(currentListIndex).vocabKanji,
                vocabList.at(currentListIndex).vocabMeaning,
                vocabList.at(currentListIndex).vocabReading
            });

            vocabListToUpdate.append({
                vocabList.at(currentListIndex).vocabId,
                vocabList.at(currentListIndex).vocabKanji,
                vocabList.at(currentListIndex).vocabMeaning,
                vocabList.at(currentListIndex).vocabReading,
                QDate::currentDate().toString("yyyy-MM-dd"),
                nextDate.toString("yyyy-MM-dd"),
                ++currentCorrectCounter,
                true
            });

            if(currentListIndex < vocabList.count() -1)
            {
                currentListIndex++;
                setItemsVal();
            }
            else
            {
                dbConnClass->UpdateDbItems(vocabQuizItemList, userId);
                return "finish";
            }

            qDebug()<<"nextdate is: "<<nextDate;
            return "get";
        }
    }

    return "pause";
}

QString VocabQuiz::skipItem()
{
    qDebug()<<"skipped Item";

    //resets correct ctr and moves the item for the next day
    if(currentListIndex < vocabList.count())
    {
        QDate nextDate = QDate::currentDate().addDays(1);
        int currentCorrectCounter = 0;

        vocabQuizItemList.append({
            vocabList.at(currentListIndex).vocabId,
            false,
            QDate::currentDate(),
            nextDate,
            currentCorrectCounter,
            vocabList.at(currentListIndex).vocabKanji,
            vocabList.at(currentListIndex).vocabMeaning,
            vocabList.at(currentListIndex).vocabReading
        });

        vocabListToUpdate.append({
            vocabList.at(currentListIndex).vocabId,
            vocabList.at(currentListIndex).vocabKanji,
            vocabList.at(currentListIndex).vocabMeaning,
            vocabList.at(currentListIndex).vocabReading,
            QDate::currentDate().toString("yyyy-MM-dd"),
            nextDate.toString("yyyy-MM-dd"),
            currentCorrectCounter,
            true
        });

        if(currentListIndex < vocabList.count() -1)
        {
            currentListIndex++;
            setItemsVal();
        }
        else
        {
            dbConnClass->UpdateDbItems(vocabQuizItemList, userId);
            return "finish";
        }
        return "get";
    }

    return "pause";
}

void VocabQuiz::clearQuizList()
{
    vocabQuizItemList.clear();
}

QString VocabQuiz::getCorrectScore()
{
    int correctCtr = 0;
    for(VocabQuizStruct &item : vocabQuizItemList)
    {
        if(item.correctCounter != 0)
            ++correctCtr;
    }
    return QString::number(correctCtr);
}

QString VocabQuiz::getIncorrectScore()
{
    int inCorrectCtr = 0;
    for(VocabQuizStruct &item : vocabQuizItemList)
    {
        if(item.correctCounter == 0)
            ++inCorrectCtr;
    }
    return QString::number(inCorrectCtr);
}

void VocabQuiz::randomizeVocabList()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    //initial values for labels in qml
    if(!vocabList.empty())
    {
        std::shuffle(vocabList.begin(), vocabList.end(), gen);

        setItemsVal();
    }
}

void VocabQuiz::setItemsVal()
{
    m_vocabMeaningTxt = vocabList.at(currentListIndex).vocabMeaning;
    emit vocabMeaningTxtChanged();

    m_vocabKanjiTxt = vocabList.at(currentListIndex).vocabKanji;
    emit vocabKanjiTxtChanged();
}

bool VocabQuiz::checkIfStringMatches(QString txtVal, QString valToCompare)
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

QStringList VocabQuiz::getValStringList(QString val)
{
    QString valString = val;
    valString = valString.simplified();
    valString.replace(',',' ');

    //for JP comma
    int indexJpComma = valString.indexOf("、");
    valString = valString.replace(indexJpComma, 1, " ");
    //for JP hypen
    int indexJpHypen = valString.indexOf("ー");
    valString = valString.replace(indexJpHypen, 1, " ");

    QStringList stringList = valString.split(" ",Qt::SkipEmptyParts);

    return stringList;
}

QDate VocabQuiz::getDaysToAddToItem(int index)
{
    int correctCtr = vocabList.at(index).correctStreak;
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
