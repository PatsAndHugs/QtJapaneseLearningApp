#ifndef KANJILIST_H
#define KANJILIST_H

#include "QObject"
#include "QVector"

class DbConnectionClass;

struct KanjiListStruct
{
    QString kanji;
    QString kunyomi;
    QString onyomi;
    QString kanjiEnglishName;

    KanjiListStruct(){
        kanji = "";
        kunyomi = "";
        onyomi = "";
        kanjiEnglishName = "";
    }

    KanjiListStruct(QString valKanji, QString valKunyomi,
                    QString valOnyomi, QString valEnglishName)
    {
        kanji = valKanji;
        kunyomi = valKunyomi;
        onyomi = valOnyomi;
        kanjiEnglishName = valEnglishName;
    }
};

class KanjiList : public QObject
{
    Q_OBJECT

public:

    explicit KanjiList(QObject *parent = nullptr);

    QVector<KanjiListStruct> items() const;

    bool setItemAt(int index, const KanjiListStruct &item);

signals:
    void preItemAppended();
    void postItemAppended();

public slots:
    void appendItem();
    void addItems();

private:
    QVector<KanjiListStruct> mItems;
    DbConnectionClass *dbClass;
};

#endif // KANJILIST_H
