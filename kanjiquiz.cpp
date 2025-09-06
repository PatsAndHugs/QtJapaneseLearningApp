#include <qdebug.h>
#include <random>
#include <algorithm>

#include "kanjiquiz.h"

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

    randomizeKanjiList();
}

void KanjiQuiz::testFunc()
{
   // QDateTime dt = QDateTime::currentDateTime();
    qDebug()<<"current date time: "<<kanjiList.at(currentListIndex).nextDateToAnswer;
}

void KanjiQuiz::randomizeKanjiList()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(kanjiList.begin(), kanjiList.end(), gen);

    //initial values for labels in qml
    if(!kanjiList.empty())
    {
        setItemsVal();
    }
}

bool KanjiQuiz::getNextItem()
{
    QDateTime currentDate = QDateTime::currentDateTime();
    //TODO get current correct counter from db if <3 add +1 day
    //if ctr >= 3 && ctr << 6 add + 3days
    //if ctr >= 6 && ctr << 9 add +7days
    //if ctr >= 9 && ctr << 12 add + 1month
    //if ctr > 12 +9999months / finished

    //PLACEHOLDER
    QDateTime nextDateAns = currentDate.addDays(3);


    if(checkIfStringMatches(m_kunyomiTxt, kanjiList.at(currentListIndex).kunyomi) &&
        checkIfStringMatches(m_onyomiTxt, kanjiList.at(currentListIndex).onyomi))
    {
        if(currentListIndex < kanjiList.count() -1)
        {
            currentListIndex++;
            setItemsVal();

            KanjiQuizItemList.append({
                kanjiList.at(currentListIndex).kanjiId,
                true,
                currentDate,
                nextDateAns
            });

            return true;
        }
    }

    return false;
}

void KanjiQuiz::skipItem()
{
    qDebug()<<"skipped Item";
    currentListIndex++;
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

    QStringList stringList = kunyomiString.split(" ",Qt::SkipEmptyParts);

    return stringList;
}

