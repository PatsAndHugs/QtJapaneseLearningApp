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
    //kanji
    Q_PROPERTY(QString kanjiText READ kanjiText WRITE setKanjiText NOTIFY kanjiTextChanged)
    //meaning
    Q_PROPERTY(QString kanjiMeaning READ kanjiMeaning WRITE setKanjiMeaning NOTIFY kanjiMeaningChanged)
    //reading
    Q_PROPERTY(QString kanjiReading READ kanjiReading WRITE setKanjiReading NOTIFY kanjiReadingChanged)

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

    void setItemToShowInLearnWindow();

private:
    QVector<VocabListStruct> mItems;
    QList<int> mSelectionList;
    QList<VocabListStruct> mSelectedItemsList;
    XMLReaderClass *xmlReader;

    QString m_kanjiText;
    QString m_kanjiMeaning;
    QString m_kanjiReading;
};

#endif // VOCABLIST_H
