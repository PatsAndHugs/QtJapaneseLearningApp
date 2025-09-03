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
    qDebug()<<"testFunc value: "<<m_kunyomiTxt;
}

void KanjiQuiz::randomizeKanjiList()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(kanjiList.begin(), kanjiList.end(), gen);

    for(const KanjiListStruct &item : std::as_const(kanjiList))
        qDebug()<<"kanji list item:  "<<item.kanjiEnglishName;

    //initial values for labels in qml
    if(!kanjiList.empty())
    {
        qDebug()<<"initialize kanjienglishnamelbl";
        setItemsVal();
    }
}

void KanjiQuiz::getNextItem()
{
    if(m_kunyomiTxt == kanjiList.at(currentListIndex).kunyomi &&
        m_onyomiTxt == kanjiList.at(currentListIndex).onyomi)
    {
        if(currentListIndex < kanjiList.count() -1)
        {
            currentListIndex++;
            setItemsVal();

            m_kunyomiTxt="";
            emit kunyomiTxtChanged();
            m_onyomiTxt="";
            emit onyomiTxtChanged();
        }
    }
}

void KanjiQuiz::setItemsVal()
{
    m_englishNameTxt = kanjiList.at(currentListIndex).kanjiEnglishName;
    emit englishNameTxtChanged();

    m_kanjiTxt = kanjiList.at(currentListIndex).kanji;
    emit kanjiTxtChanged();

    m_kunyomiTxt = kanjiList.at(currentListIndex).kunyomi;
    emit kunyomiTxtChanged();

    m_onyomiTxt = kanjiList.at(currentListIndex).onyomi;
    emit onyomiTxtChanged();
}
