#ifndef KANJILIST_H
#define KANJILIST_H

#include <QObject>
#include <QVector>

#include "xmlreaderclass.h"


class DbConnectionClass;
class ApiConnectionClass;


struct KanjiListStruct
{
    QString kanjiId;
    QString kanji;
    QString kunyomi;
    QString onyomi;
    QString kanjiEnglishName;
    QString lastDateAnswered;
    QString nextDateToAnswer;
    int correctStreak;
    bool isSelected;

    KanjiListStruct(){
    }

    KanjiListStruct(QString valKanjiId, QString valKanji, QString valKunyomi,
                    QString valOnyomi, QString valEnglishName, QString valLastDateAnswered,
                    QString valNextDateToAnswer, int valCorrectStreak, bool valIsSelected)
    {
        kanjiId = valKanjiId;
        kanji = valKanji;
        kunyomi = valKunyomi;
        onyomi = valOnyomi;
        kanjiEnglishName = valEnglishName;
        lastDateAnswered = valLastDateAnswered;
        nextDateToAnswer = valNextDateToAnswer;
        correctStreak = valCorrectStreak;
        isSelected = valIsSelected;
    }
};

class KanjiList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString englishNameTxt READ englishNameTxt WRITE setEnglishNameTxt NOTIFY englishNameTxtChanged)
    Q_PROPERTY(QString kanjiTxt READ kanjiTxt WRITE setKanjiTxt NOTIFY kanjiTxtChanged)
    Q_PROPERTY(QString kunyomiTxt READ kunyomiTxt WRITE setKunyomiTxt NOTIFY kunyomiTxtChanged)
    Q_PROPERTY(QString onyomiTxt READ onyomiTxt WRITE setOnyomiTxt NOTIFY onyomiTxtChanged)

public:

    explicit KanjiList(QObject *parent = nullptr);

    QVector<KanjiListStruct> items() const;

    bool setItemAt(int index, const KanjiListStruct &item);
    QList<int> getSelectionList(){return mSelectionList;}

    QString englishNameTxt(){return m_englishNameTxt;}
    void setEnglishNameTxt(QString newVal);

    QString kanjiTxt(){return m_kanjiTxt;}
    void setKanjiTxt(QString newVal);

    QString kunyomiTxt(){return m_kunyomiTxt;}
    void setKunyomiTxt(QString newVal);

    QString onyomiTxt(){return m_onyomiTxt;}
    void setOnyomiTxt(QString newVal);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved();
    void postItemRemoved();
    void postIsSelectedChanged();

    void englishNameTxtChanged();
    void kanjiTxtChanged();
    void kunyomiTxtChanged();
    void onyomiTxtChanged();

public slots:
    void appendItem();
    void addItems();
    void clearItems();
    void updateLastItemIsSelected(int count);
    void updateAllItemsIsSelected();
    void clearAllSelectedItems();
    void updateAllCurrentDateItemsIsSelected();
    void addSelectedItemsToList();
    QList<KanjiListStruct> getSelectedItemsList(){return mSelectedItemsList;}
    int getSelectedItemsCount();
    void addNewListItems();
    void updateListDatesAfteResult(QList<KanjiListStruct> list);

    void setItemToShowInLearnWindow();

private:
    QVector<KanjiListStruct> mItems;
    DbConnectionClass *dbClass;
    QList<int> mSelectionList;
    QList<KanjiListStruct> mSelectedItemsList;
    XMLReaderClass *xmlReader;
    ApiConnectionClass *apiConnClass;

    QString m_englishNameTxt = "kappa";
    QString m_kanjiTxt;
    QString m_kunyomiTxt;
    QString m_onyomiTxt;
};

#endif // KANJILIST_H
