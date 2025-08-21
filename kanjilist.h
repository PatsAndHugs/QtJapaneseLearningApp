#ifndef KANJILIST_H
#define KANJILIST_H

#include "QObject"
#include "QVector"

struct KanjiListStruct
{
    QString kanji;
    QString kunyomi;
    QString onyomi;
    QString KanjiEnglishName;
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
    void addItems(QList<KanjiListStruct> listToAdd);

private:
    QVector<KanjiListStruct> mItems;
};

#endif // KANJILIST_H
