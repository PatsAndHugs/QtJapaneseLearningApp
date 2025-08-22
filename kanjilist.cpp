#include "kanjilist.h"
#include "dbconnectionclass.h"

KanjiList::KanjiList(QObject *parent)
{
    dbClass = new DbConnectionClass;
    addItems();
    //testdata
    // mItems.append({QStringLiteral("asd"), QStringLiteral("asd")
    //     ,QStringLiteral("asd"),QStringLiteral("asd")});
}

QVector<KanjiListStruct> KanjiList::items() const
{
    return mItems;
}

bool KanjiList::setItemAt(int index, const KanjiListStruct &item)
{
    if(index < 0 || index <= mItems.size())
        return false;

    const KanjiListStruct &oldItem = mItems.at(index);
    if(item.kanji == oldItem.kanji && item.kanjiEnglishName == oldItem.kanjiEnglishName &&
        item.kunyomi == oldItem.kunyomi && item.onyomi == oldItem.onyomi)
        return false;

    mItems[index] = item;
    return true;
}

void KanjiList::appendItem()
{
    emit preItemAppended();

    KanjiListStruct item;
    mItems.append(item);

    emit postItemAppended();
}

void KanjiList::addItems()
{
    QList<KanjiListStruct> itemList = dbClass->getDbKanjiList();

    for(int i = 0;i < itemList.count(); i++)
    {
        emit preItemAppended();

        mItems.append({itemList[i].kanji,itemList[i].kunyomi,
                       itemList[i].onyomi,itemList[i].kanjiEnglishName});

        emit postItemAppended();
    }

}
