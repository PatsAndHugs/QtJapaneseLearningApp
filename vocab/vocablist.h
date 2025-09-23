#ifndef VOCABLIST_H
#define VOCABLIST_H

#include <QObject>
#include <QVector>

#include "xmlreaderclass.h"

class DbConnectionClass;

struct VocabListStruct
{
    QString vocabId;
    QString vocabKanji;
    QString vocabMeaning;
    QString vocabReading;
    QString lastDateAnswered;
    QString nextDateToAnswer;
    int correctStreak;
    bool isSelected;

    VocabListStruct(){
    }

    VocabListStruct(QString valVocabId, QString valVocab,QString valVocabMeaning,
                    QString valVocabReading, QString valLastDateAnswered,
                    QString valNextDateToAnswer, int valCorrectStreak,
                    bool valIsSelected)
    {
        vocabId = valVocabId;
        vocabKanji = valVocab;
        vocabMeaning = valVocabMeaning;
        vocabReading = valVocabReading;
        lastDateAnswered = valLastDateAnswered;
        nextDateToAnswer = valNextDateToAnswer;
        correctStreak = valCorrectStreak;
        isSelected = valIsSelected;
    }
};

class VocabList : public QObject
{
    Q_OBJECT

public:

    explicit VocabList(QObject *parent = nullptr);

    QVector<VocabListStruct> items() const;

    bool setItemAt(int index, const VocabListStruct &item);
    QList<int> getSelectionList(){return mSelectionList;}

signals:
    void preVocabItemAppended();
    void postVocabItemAppended();

    void preVocabItemRemoved();
    void postVocabItemRemoved();
    void postVocabIsSelectedChanged();

public slots:
    void appendItem();
    void addItems();
    void clearItems();
    void updateLastItemIsSelected(int count);
    void updateAllItemsIsSelected();
    void updateAllCurrentDateItemsIsSelected();
    void addSelectedItemsToList();
    QList<VocabListStruct> getSelectedItemsList(){return mSelectedItemsList;}
    int getSelectedItemsCount();
    void addNewListItems();
    void updateListDatesAfteResult(QList<VocabListStruct> list);

private:
    QVector<VocabListStruct> mItems;
    DbConnectionClass *dbClass;
    QList<int> mSelectionList;
    QList<VocabListStruct> mSelectedItemsList;
    XMLReaderClass *xmlReader;
};

#endif // VOCABLIST_H
