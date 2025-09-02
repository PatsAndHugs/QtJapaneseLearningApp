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

private:

    KanjiList *kanjiListClass;

    QList<KanjiListStruct> kanjiList;

    void getKanjiList();
};

#endif // KANJIQUIZ_H
