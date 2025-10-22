#include "vocablist.h"
#include "network/apiconnectionclass.h"

VocabList::VocabList(QObject *parent)
{
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
    mItems.clear();
    std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
    apiConnClass->fetchVocabListForUser();

    QEventLoop loop;
    connect(apiConnClass.get(), &ApiConnectionClass::vocabOutputListChanged, &loop, &QEventLoop::quit);

    connect(apiConnClass.get(), &ApiConnectionClass::vocabOutputListChanged,this, [&](){
        QList<VocabListStruct> itemList = apiConnClass->getVocabOutputList();
        for(int i = 0;i < itemList.count(); i++)
        {
            emit preVocabItemAppended();

            mItems.append({itemList[i].vocabId,itemList[i].vocabKanji,itemList[i].vocabMeaning,
                           itemList[i].vocabReading,itemList[i].lastDateAnswered,
                           itemList[i].nextDateToAnswer,itemList[i].correctStreak,
                           itemList[i].isSelected});

            emit postVocabItemAppended();
        }
        emit fetchedVocabListFromApi();
    });

    loop.exec();
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
    std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
    apiConnClass->fetchAdditionalVocabListForUser();

    QEventLoop loop;
    connect(apiConnClass.get(), &ApiConnectionClass::newVocabListChanged, &loop, &QEventLoop::quit);

    connect(apiConnClass.get(), &ApiConnectionClass::newVocabListChanged,this, [&](){
        QList<VocabListStruct> itemList = apiConnClass->getNewVocabListToAdd();
        for(int i = 0;i < itemList.count(); i++)
        {
            emit preVocabItemAppended();

            mItems.append({itemList[i].vocabId,itemList[i].vocabKanji,itemList[i].vocabMeaning,
                           itemList[i].vocabReading,itemList[i].lastDateAnswered,
                           itemList[i].nextDateToAnswer,itemList[i].correctStreak,
                           itemList[i].isSelected});

            emit postVocabItemAppended();
        }
    });

    loop.exec();
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
