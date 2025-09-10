#include "kanjilist.h"
#include "dbconnectionclass.h"
#include <qforeach.h>

KanjiList::KanjiList(QObject *parent)
{
    dbClass = new DbConnectionClass;
    addItems();

    //testdata
    // mItems.append({QStringLiteral("KJ-1"),QStringLiteral("月"), QStringLiteral("げつ、がつ")
    //                ,QStringLiteral("ツキ"),QStringLiteral("moon"), QStringLiteral("09/06/25")
    //                ,QStringLiteral("09/06/25"),1,false});
    // mItems.append({QStringLiteral("KJ-2"),QStringLiteral("日"), QStringLiteral("ひ、よう")
    //                ,QStringLiteral("ニチ、ジツ"),QStringLiteral("sun"),QStringLiteral("09/06/25")
    //                ,QStringLiteral("09/06/25"),4,false});
    // mItems.append({QStringLiteral("KJ-3"),QStringLiteral("妹"), QStringLiteral("いもうと")
    //                ,QStringLiteral("マイ"),QStringLiteral("younger sister"),QStringLiteral("09/06/25")
    //                ,QStringLiteral("09/06/25"),10,false});
    // mItems.append({QStringLiteral("KJ-4"),QStringLiteral("姉"), QStringLiteral("あね、はは")
    //                ,QStringLiteral("シ"),QStringLiteral("elder sister"), QStringLiteral("09/06/25")
    //                ,QStringLiteral("09/06/25"),14,false});
    // mItems.append({QStringLiteral("KJ-5"),QStringLiteral("星"), QStringLiteral("ほし")
    //                ,QStringLiteral("セイ、ショウ"),QStringLiteral("star"), QStringLiteral("09/06/25")
    //                ,QStringLiteral("09/06/25"),13,false});

}

QVector<KanjiListStruct> KanjiList::items() const
{
    return mItems;
}

bool KanjiList::setItemAt(int index, const KanjiListStruct &item)
{
    if(index < 0 || index >= mItems.size())
        return false;


    const KanjiListStruct &oldItem = mItems.at(index);
    if(item.kanjiId == oldItem.kanjiId
        && item.kanji == oldItem.kanji
        && item.kunyomi == oldItem.kunyomi
        && item.onyomi == oldItem.onyomi
        && item.kanjiEnglishName == oldItem.kanjiEnglishName
        && item.lastDateAnswered == oldItem.lastDateAnswered
        && item.nextDateToAnswer == oldItem.nextDateToAnswer
        && item.correctStreak == oldItem.correctStreak
        && item.isSelected == oldItem.isSelected)
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

        mItems.append({itemList[i].kanjiId,itemList[i].kanji,itemList[i].kunyomi,
                       itemList[i].onyomi,itemList[i].kanjiEnglishName,itemList[i].lastDateAnswered,
                       itemList[i].nextDateToAnswer,itemList[i].correctStreak ,
                       itemList[i].isSelected});

        emit postItemAppended();
    }
}

void KanjiList::updateLastItemIsSelected(int count)
{
    if(count > mItems.count())
        return;

    int lastIndex = mItems.count() - count;
    qDebug()<<mItems.count();

    for(int i = lastIndex;i < mItems.count(); i++)
    {
        mItems[i].isSelected = true;
        mSelectionList.append(i);
        emit postIsSelectedChanged();
        qDebug()<<mItems[i].isSelected;
    }
}

void KanjiList::updateAllItemsIsSelected()
{
    updateLastItemIsSelected(mItems.count());
}

void KanjiList::addSelectedItemsToList()
{
    mSelectedItemsList.clear();
    for(const KanjiListStruct &item : std::as_const(mItems))
    {
        if(item.isSelected == true)
            mSelectedItemsList.append(item);
    }

    for(const auto &item : std::as_const(mSelectedItemsList))
    {
        qDebug()<<"selected items newList: "<<item.kanjiId;

    }
}

int KanjiList::getSelectedItemsCount()
{
    int selectedItemsCount = 0;

    for(const KanjiListStruct &item : std::as_const(mItems))
    {
        if(item.isSelected == true)
            selectedItemsCount++;
    }
    return selectedItemsCount;
}
