#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include <QObject>
#include <QQmlProperty>
#include <QDateTime>

#include "vocablist.h"

struct VocabListStruct;

struct VocabQuizStruct
{
    QString vocabId;
    bool isAnswerCorrect;
    QDate dateAnswered;
    QDate nextDateToAnswer;
    int correctCounter;
    QString vocabKanji;
    QString vocabMeaning;
    QString vocabReading;
};

class VocabQuiz : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vocabMeaningTxt READ vocabMeaningTxt WRITE setVocabMeaningTxt NOTIFY vocabMeaningTxtChanged)
    Q_PROPERTY(QString vocabKanjiTxt READ vocabKanjiTxt WRITE setVocabKanjiTxt NOTIFY vocabKanjiTxtChanged)
    Q_PROPERTY(QString vocabReadingTxt READ vocabReadingTxt WRITE setVocabReadingTxt NOTIFY vocabReadingTxtChanged)

public:

    explicit VocabQuiz(QObject *parent = nullptr);

    QString vocabMeaningTxt(){return m_vocabMeaningTxt;}
    void setVocabMeaningTxt(QString newVal);

    QString vocabKanjiTxt(){return m_vocabKanjiTxt;}
    void setVocabKanjiTxt(QString newVal);

    QString vocabReadingTxt(){return m_vocabReadingTxt;}
    void setVocabReadingTxt(QString newVal);

public slots:

    void getVocabList(QList<VocabListStruct> list);
    //get = get next; pause = do nothing; finish = end of items reached
    void getNextItem();
    //get = get next; pause = do nothing; finish = end of items reached
    void skipItem();

    QList<VocabQuizStruct> getResultList(){return vocabQuizItemList;}

    QList<VocabListStruct> getVocabListToUpdate(){return vocabListToUpdate;}

    void clearQuizList();

    QString getCorrectScore();
    QString getIncorrectScore();

signals:

    void vocabMeaningTxtChanged();
    void vocabKanjiTxtChanged();
    void vocabReadingTxtChanged();
    void getNextItemTriggered();
    void quizFinished();
    void tallyWindowLoading();

private:

    VocabList *vocabListClass;

    QList<VocabListStruct> vocabList;

    QList<VocabListStruct> vocabListToUpdate;

    void randomizeVocabList();

    QString m_vocabMeaningTxt;
    QString m_vocabKanjiTxt;
    QString m_vocabReadingTxt;

    int currentListIndex = 0;
    //set m_englishnameTxt and m_kanjiTxt to the current item
    //in the list base on the currentindex
    void setItemsVal();

    bool checkIfStringMatches(QString txtVal, QString valToCompare);
    QStringList getValStringList(QString val);

    QList<VocabQuizStruct> vocabQuizItemList;

    QDate getDaysToAddToItem(int index);
};

#endif // VOCABQUIZ_H
