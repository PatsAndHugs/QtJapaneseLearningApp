#ifndef KANJIQUIZ_H
#define KANJIQUIZ_H

#include <QObject>
#include <QQmlProperty>
#include <QDateTime>

#include "kanjilist.h"

struct KanjiListStruct;

struct KanjiQuizStruct
{
    QString kaniId;
    bool isAnswerCorrect;
    QDate dateAnswered;
    QDate nextDateToAnswer;
    int correctCounter;
};

class KanjiQuiz : public  QObject
{
    Q_OBJECT
    Q_PROPERTY(QString englishNameTxt READ englishNameTxt WRITE setEnglishNameTxt NOTIFY englishNameTxtChanged)
    Q_PROPERTY(QString kanjiTxt READ kanjiTxt WRITE setKanjiTxt NOTIFY kanjiTxtChanged)
    Q_PROPERTY(QString kunyomiTxt READ kunyomiTxt WRITE setKunyomiTxt NOTIFY kunyomiTxtChanged)
    Q_PROPERTY(QString onyomiTxt READ onyomiTxt WRITE setOnyomiTxt NOTIFY onyomiTxtChanged)

public:

    explicit KanjiQuiz(QObject *parent = nullptr);

    QString englishNameTxt(){return m_englishNameTxt;}
    void setEnglishNameTxt(QString newVal);

    QString kanjiTxt(){return m_kanjiTxt;}
    void setKanjiTxt(QString newVal);

    QString kunyomiTxt(){return m_kunyomiTxt;}
    void setKunyomiTxt(QString newVal);

    QString onyomiTxt(){return m_onyomiTxt;}
    void setOnyomiTxt(QString newVal);

public slots:

    void getKanjiList(QList<KanjiListStruct> list);
    void testFunc();
    //get = get next; pause = do nothing; finish = end of items reached
    QString getNextItem();
    //get = get next; pause = do nothing; finish = end of items reached
    QString skipItem();

signals:

    void englishNameTxtChanged();
    void kanjiTxtChanged();
    void kunyomiTxtChanged();
    void onyomiTxtChanged();

private:

    KanjiList *kanjiListClass;

    QList<KanjiListStruct> kanjiList;

    void randomizeKanjiList();

    QString m_englishNameTxt;
    QString m_kanjiTxt;
    QString m_kunyomiTxt;
    QString m_onyomiTxt;

    int currentListIndex = 0;
    //set m_englishnameTxt and m_kanjiTxt to the current item
    //in the list base on the currentindex
    void setItemsVal();

    bool checkIfStringMatches(QString txtVal, QString valToCompare);
    QStringList getValStringList(QString val);

    QList<KanjiQuizStruct> kanjiQuizItemList;

    QDate getDaysToAddToItem(int index);
};

#endif // KANJIQUIZ_H
