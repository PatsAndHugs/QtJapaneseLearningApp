#include "kanjiquiz.h"

KanjiQuiz::KanjiQuiz(QObject *parent)
{
    kanjiListClass = new KanjiList;
}

void KanjiQuiz::getKanjiList()
{
    kanjiList = kanjiListClass->getSelectedItemsList();
}
