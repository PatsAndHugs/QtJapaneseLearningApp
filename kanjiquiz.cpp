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

void KanjiQuiz::getKanjiList(QList<KanjiListStruct> list)
{
    kanjiList = list;
    qDebug()<<"getKanjiList"<<kanjiList.count();

    randomizeKanjiList();
}

void KanjiQuiz::testFunc()
{
    m_englishNameTxt = "Kappa";
    qDebug()<<"testFunc kanjilist count: "<<kanjiList.count();
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

        m_englishNameTxt = kanjiList.at(0).kanjiEnglishName;
        emit englishNameTxtChanged();

        m_kanjiTxt = kanjiList.at(0).kanji;
        emit kanjiTxtChanged();
    }
}
