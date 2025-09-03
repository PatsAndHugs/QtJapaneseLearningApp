#ifndef KANJIQUIZ_H
#define KANJIQUIZ_H

#include <QObject>

#include "kanjilist.h"

struct KanjiListStruct;

class KanjiQuiz : public  QObject
{
    Q_OBJECT
    Q_PROPERTY(QString englishNameTxt READ englishNameTxt WRITE setEnglishNameTxt NOTIFY englishNameTxtChanged)
    Q_PROPERTY(QString kanjiTxt READ kanjiTxt WRITE setKanjiTxt NOTIFY kanjiTxtChanged)

public:

    explicit KanjiQuiz(QObject *parent = nullptr);

    QString englishNameTxt(){return m_englishNameTxt;}
    void setEnglishNameTxt(QString newVal);

    QString kanjiTxt(){return m_kanjiTxt;}
    void setKanjiTxt(QString newVal);


public slots:

    void getKanjiList(QList<KanjiListStruct> list);
    void testFunc();

signals:
    void englishNameTxtChanged();
    void kanjiTxtChanged();

private:

    KanjiList *kanjiListClass;

    QList<KanjiListStruct> kanjiList;

    void randomizeKanjiList();

    QString m_englishNameTxt;
    QString m_kanjiTxt;
};

#endif // KANJIQUIZ_H
