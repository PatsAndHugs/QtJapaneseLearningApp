#ifndef KANJILIST_H
#define KANJILIST_H

#include <QObject>
#include <QVector>

class DbConnectionClass;

struct KanjiListStruct
{
    QString kanji;
    QString kunyomi;
    QString onyomi;
    QString kanjiEnglishName;
    bool isSelected;

    KanjiListStruct(){
    }

    KanjiListStruct(QString valKanji, QString valKunyomi,
                    QString valOnyomi, QString valEnglishName, bool valIsSelected)
    {
        kanji = valKanji;
        kunyomi = valKunyomi;
        onyomi = valOnyomi;
        kanjiEnglishName = valEnglishName;
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

private:
    QVector<KanjiListStruct> mItems;
    DbConnectionClass *dbClass;
    QList<int> mSelectionList;
};

#endif // KANJILIST_H
