#ifndef KANJIQUIZ_H
#define KANJIQUIZ_H

#include <QObject>

#include "kanjilist.h"

struct KanjiListStruct;

class KanjiQuiz : public  QObject
{
    Q_OBJECT

public:

    explicit KanjiQuiz(QObject *parent = nullptr);

public slots:

    void getKanjiList(QList<KanjiListStruct> list);

private:

    KanjiList *kanjiListClass;

    QList<KanjiListStruct> kanjiList;

    QList<int> randomListNumbers;
    void setRandomListNumbers();
};

#endif // KANJIQUIZ_H
