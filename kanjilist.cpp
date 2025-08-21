#include "kanjilist.h"


KanjiList::KanjiList(QObject *parent)
{
    //testdata
    //mItems.append({true, QStringLiteral("asd")});
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

void KanjiList::addItems(QList<KanjiListStruct> listToAdd)
{
    for(int i = 0;i < listToAdd.count(); i++)
    {
        emit preItemAppended();

        mItems.append({listToAdd[i].kanji,listToAdd[i].kunyomi,
                       listToAdd[i].onyomi,listToAdd[i].kanjiEnglishName});

        emit postItemAppended();
    }

}
