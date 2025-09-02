#include <qdebug.h>
#include <random>
#include <algorithm>
#include "kanjiquiz.h"

KanjiQuiz::KanjiQuiz(QObject *parent)
{
}

void KanjiQuiz::getKanjiList(QList<KanjiListStruct> list)
{
    kanjiList = list;
    qDebug()<<"getKanjiList"<<kanjiList.count();

    setRandomListNumbers();
}

void KanjiQuiz::setRandomListNumbers()
{
    for(int i = 0; i < kanjiList.count(); i++)
        randomListNumbers.append(i);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(randomListNumbers.begin(), randomListNumbers.end(), gen);
    qDebug()<<"randomListNumbers Count "<<randomListNumbers.count();

}
