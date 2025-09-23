#include "vocablist.h"
#include "dbconnectionclass.h"

VocabList::VocabList(QObject *parent)
{
    dbClass = new DbConnectionClass;

    xmlReader = new XMLReaderClass;
    if(xmlReader->getLoggedinStatus() == "true")
    {
        addItems();
        qDebug()<<"vocablist constructor";
    }
}

QVector<VocabListStruct> VocabList::items() const
{
    return mItems;
}

bool VocabList::setItemAt(int index, const VocabListStruct &item)
{
    if(index < 0 || index >= mItems.size())
        return false;

    const VocabListStruct &oldItem = mItems.at(index);
    if(item.vocabId == oldItem.vocabId
        && item.vocabKanji == oldItem.vocabKanji
        && item.vocabMeaning == oldItem.vocabMeaning
        && item.vocabReading == oldItem.vocabReading
        && item.lastDateAnswered == oldItem.lastDateAnswered
        && item.nextDateToAnswer == oldItem.nextDateToAnswer
        && item.correctStreak == oldItem.correctStreak
        && item.isSelected == oldItem.isSelected)
        return false;

    mItems[index] = item;
    return true;
}

void VocabList::appendItem()
{
    emit preVocabItemAppended();

    VocabListStruct item;
    mItems.append(item);

    emit postVocabItemAppended();
}

void VocabList::addItems()
{
    xmlReader->loadDocument("Config.xml");
    QString userId = xmlReader->getSavedUserInfo().at(0);
    dbClass->populateVocabModelList(userId);
    qDebug()<<"addItems userid "<<userId;
    QList<VocabListStruct> itemList = dbClass->getDbVocabList();

    for(int i = 0;i < itemList.count(); i++)
    {
        emit preVocabItemAppended();

        mItems.append({itemList[i].vocabId,itemList[i].vocabKanji,itemList[i].vocabMeaning,
                       itemList[i].vocabReading,itemList[i].lastDateAnswered,
                       itemList[i].nextDateToAnswer,itemList[i].correctStreak,
                       itemList[i].isSelected});

        emit postVocabItemAppended();
    }
}

void VocabList::clearItems()
{
    dbClass->clearDbVocabList();
    emit preVocabItemRemoved();
    mItems.clear();
    emit postVocabItemRemoved();

    qDebug()<<"clear "<<mItems.count();
}

void VocabList::updateLastItemIsSelected(int count)
{
    if(count > mItems.count())
        return;

    int lastIndex = mItems.count() - count;

    for(int i = lastIndex;i < mItems.count(); i++)
    {
        mItems[i].isSelected = true;
        mSelectionList.append(i);
        emit postVocabIsSelectedChanged();
        qDebug()<<mItems[i].isSelected;
    }
}

void VocabList::updateAllItemsIsSelected()
{
    updateLastItemIsSelected(mItems.count());
}

void VocabList::updateAllCurrentDateItemsIsSelected()
{
    if(mItems.isEmpty())
        return;

    for(int i = 0;i < mItems.count(); i++)
    {
        QDate itemNextDate = QDate::fromString(mItems.at(i).nextDateToAnswer,
                                               "yyyy-MM-dd");

        if(itemNextDate == QDate::currentDate() || itemNextDate < QDate::currentDate())
        {
            mItems[i].isSelected = true;
            mSelectionList.append(i);
            emit postVocabIsSelectedChanged();
        }
    }
}

void VocabList::addSelectedItemsToList()
{
    mSelectedItemsList.clear();
    for(const VocabListStruct &item : std::as_const(mItems))
    {
        if(item.isSelected == true)
            mSelectedItemsList.append(item);
    }

    for(const auto &item : std::as_const(mSelectedItemsList))
    {
        qDebug()<<"selected items newList: "<<item.vocabId;

    }
}

int VocabList::getSelectedItemsCount()
{
    int selectedItemsCount = 0;

    for(const VocabListStruct &item : std::as_const(mItems))
    {
        if(item.isSelected == true)
            selectedItemsCount++;
    }
    return selectedItemsCount;
}

void VocabList::addNewListItems()
{
    xmlReader->loadDocument("Config.xml");
    QString userId = xmlReader->getSavedUserInfo().at(0);
    dbClass->insertVocabItemForUser(userId);
    qDebug()<<"addItems userid "<<userId;
    QList<VocabListStruct> itemList = dbClass->getAppendVocabList();

    for(int i = 0;i < itemList.count(); i++)
    {
        emit preVocabItemAppended();

        mItems.append({itemList[i].vocabId,itemList[i].vocabKanji,itemList[i].vocabMeaning,
                       itemList[i].vocabReading,itemList[i].lastDateAnswered,
                       itemList[i].nextDateToAnswer,itemList[i].correctStreak,
                       itemList[i].isSelected});

        emit postVocabItemAppended();
    }
}

void VocabList::updateListDatesAfteResult(QList<VocabListStruct> list)
{
    if(list.isEmpty())
        return;

    for(VocabListStruct &item : list)
    {
        for(VocabListStruct &localItem : mItems)
        {
            if(item.vocabId == localItem.vocabId)
            {
                localItem.lastDateAnswered = item.lastDateAnswered;
                localItem.nextDateToAnswer = item.nextDateToAnswer;
                localItem.correctStreak = item.correctStreak;
            }
        }
    }
}
