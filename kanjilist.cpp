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
    if(item.Kanji == oldItem.Kanji && item.KanjiEnglishName == oldItem.KanjiEnglishName &&
        item.Kunyomi == oldItem.Kunyomi && item.Onyomi == oldItem.Onyomi)
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
