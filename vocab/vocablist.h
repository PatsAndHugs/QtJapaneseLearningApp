#ifndef VOCABLIST_H
#define VOCABLIST_H

#include <QObject>
#include <QVector>

#include "xmlreaderclass.h"

struct VocabListStruct
{
    QString vocabId;
    QString vocabKanji;
    QString vocabMeaning;
    QString vocabReading;
    QString lastDateAnswered;
    QString nextDateToAnswer;
    QString jlptLevel;
    int correctStreak;
    bool isSelected;

    VocabListStruct(){
    }

    VocabListStruct(QString valVocabId, QString valVocab,QString valVocabMeaning,
                    QString valVocabReading, QString valLastDateAnswered,
                    QString valNextDateToAnswer, QString valJlptLevel,int valCorrectStreak,
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
        jlptLevel = valJlptLevel;
    }
};

struct VocabDetailsStruct
{
    QString wordType;
    QString vocabMeaning;

    VocabDetailsStruct(){}

    VocabDetailsStruct(QString wordTypeVal, QString vocabMeaningVal)
    {
        wordType = wordTypeVal;
        vocabMeaning = vocabMeaningVal;
    }
};

class VocabList : public QObject
{
    Q_OBJECT
    //kanji
    Q_PROPERTY(QString kanjiText READ kanjiText WRITE setKanjiText NOTIFY kanjiTextChanged)
    //meaning
    Q_PROPERTY(QString kanjiMeaning READ kanjiMeaning WRITE setKanjiMeaning NOTIFY kanjiMeaningChanged)
    //reading
    Q_PROPERTY(QString kanjiReading READ kanjiReading WRITE setKanjiReading NOTIFY kanjiReadingChanged)
    //jlptlvl
    Q_PROPERTY(QString jlptLevel READ jlptLevel WRITE setJlptLevel NOTIFY jlptLevelChanged)

public:

    explicit VocabList(QObject *parent = nullptr);

    QVector<VocabListStruct> items() const;

    bool setItemAt(int index, const VocabListStruct &item);
    QList<int> getSelectionList(){return mSelectionList;}

    QString kanjiText(){return m_kanjiText;}
    void setKanjiText(QString newVal);

    QString kanjiMeaning(){return m_kanjiMeaning;}
    void setKanjiMeaning(QString newVal);

    QString kanjiReading(){return m_kanjiReading;}
    void setKanjiReading(QString newVal);

    QString jlptLevel(){return m_jlptLevel;}
    void setJlptLevel(QString newVal);

signals:
    void preVocabItemAppended();
    void postVocabItemAppended();

    void preVocabItemRemoved();
    void postVocabItemRemoved();
    void postVocabIsSelectedChanged();

    void fetchedVocabListFromApi();
    void fetchedNewVocabListFromApi();
    void fetchedVocabListFromApiForLearning();

    void kanjiTextChanged();
    void kanjiMeaningChanged();
    void kanjiReadingChanged();

    void vocabDetailsListChanged();
    void jlptLevelChanged();

public slots:
    void appendItem();
    void addItems();
    void addItemsForLearning();
    void updateLastItemIsSelected(int count);
    void updateAllItemsIsSelected();
    void updateAllCurrentDateItemsIsSelected();
    void addSelectedItemsToList();
    QList<VocabListStruct> getSelectedItemsList(){return mSelectedItemsList;}
    int getSelectedItemsCount();
    void addNewListItems();
    void updateListDatesAfteResult(QList<VocabListStruct> list);
    void clearAllSelectedItems();
    void setItemToShowInLearnWindow();

    QList<VocabDetailsStruct> getVocabDetailsList(){return vocabDetailsList;}

private:
    QVector<VocabListStruct> mItems;
    QList<int> mSelectionList;
    QList<VocabListStruct> mSelectedItemsList;
    XMLReaderClass *xmlReader;

    QString m_kanjiText;
    QString m_kanjiMeaning;
    QString m_kanjiReading;
    QString m_jlptLevel;

    QList<VocabDetailsStruct> vocabDetailsList;
};

#endif // VOCABLIST_H
