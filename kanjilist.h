#ifndef KANJILIST_H
#define KANJILIST_H

#include <QObject>
#include <QVector>

class DbConnectionClass;

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

public:

    explicit KanjiList(QObject *parent = nullptr);

    QVector<KanjiListStruct> items() const;

    bool setItemAt(int index, const KanjiListStruct &item);
    QList<int> getSelectionList(){return mSelectionList;}

signals:
    void preItemAppended();
    void postItemAppended();

    void postIsSelectedChanged();

public slots:
    void appendItem();
    void addItems();
    void updateLastItemIsSelected(int count);
    void updateAllItemsIsSelected();
    void addSelectedItemsToList();
    QList<KanjiListStruct> getSelectedItemsList(){return mSelectedItemsList;}
    int getSelectedItemsCount();

private:
    QVector<KanjiListStruct> mItems;
    DbConnectionClass *dbClass;
    QList<int> mSelectionList;
    QList<KanjiListStruct> mSelectedItemsList;
};

#endif // KANJILIST_H
