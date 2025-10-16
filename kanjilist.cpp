#include "kanjilist.h"
#include "dbconnectionclass.h"
#include <qforeach.h>
#include "network/apiconnectionclass.h"

KanjiList::KanjiList(QObject *parent)
{
    dbClass = new DbConnectionClass;
    xmlReader = new XMLReaderClass;

    if(xmlReader->getLoggedinStatus() == "true")
    {
        //addItems();
        qDebug()<<"kanjilist constructor";
    }
    addApiConnClass = new ApiConnectionClass(this);
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

void KanjiList::setEnglishNameTxt(QString newVal)
{
    m_englishNameTxt = newVal;
}

void KanjiList::setKanjiTxt(QString newVal)
{
    m_kanjiTxt = newVal;
}

void KanjiList::setKunyomiTxt(QString newVal)
{
    m_kunyomiTxt = newVal;
}

void KanjiList::setOnyomiTxt(QString newVal)
{
    m_onyomiTxt = newVal;
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
    //ApiConnectionClass *apiConnClass = new ApiConnectionClass(this);
    addApiConnClass->fetchKanjiListForUser();

    connect(addApiConnClass, &ApiConnectionClass::kanjiOutputListChanged,this, [=](){
        QList<KanjiListStruct> itemList = addApiConnClass->getKanjiOutputList();
        for(int i = 0;i < itemList.count(); i++)
        {
            emit preItemAppended();
            mItems.append({itemList[i].kanjiId,itemList[i].kanji,itemList[i].kunyomi,
                           itemList[i].onyomi,itemList[i].kanjiEnglishName,itemList[i].lastDateAnswered,
                           itemList[i].nextDateToAnswer,itemList[i].correctStreak ,
                           itemList[i].isSelected});

            emit postItemAppended();
        }
        emit fetchedKanjiListFromApi();

    });

    connect(this, &KanjiList::fetchedNewKanjiListFromApi, this, [this](){
        delete addApiConnClass;
        addApiConnClass = nullptr;
    });
}

void KanjiList::clearItems()
{
    dbClass->clearDbKanjiList();
    emit preItemRemoved();
    mItems.clear();
    emit postItemRemoved();

    qDebug()<<"clear "<<mItems.count();
}

void KanjiList::updateLastItemIsSelected(int count)
{
    if(count > mItems.count())
        return;

    int lastIndex = mItems.count() - count;

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

void KanjiList::clearAllSelectedItems()
{

    for(int i = 0;i < mItems.count(); i++)
    {
        mItems[i].isSelected = false;
        mSelectionList.append(i);
        emit postIsSelectedChanged();
        qDebug()<<"clearAllSelectedItems"<<mItems[i].isSelected;
    }
}

void KanjiList::updateAllCurrentDateItemsIsSelected()
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
            emit postIsSelectedChanged();
        }
    }
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

void KanjiList::addNewListItems()
{
    // xmlReader->loadDocument("Config.xml");
    // QString userId = xmlReader->getSavedUserInfo().at(0);
    // dbClass->insertKanjiItemForUser(userId);
    // qDebug()<<"addItems userid "<<userId;
    // QList<KanjiListStruct> itemList = dbClass->getAppendKanjiList();
    ApiConnectionClass *apiConnClass = new ApiConnectionClass;
    apiConnClass->fetchAdditionalKanjiListForUser();
    connect(apiConnClass, &ApiConnectionClass::newKanjiListChanged,this, [=](){
        QList<KanjiListStruct> itemList = apiConnClass->getNewKanjiListToAdd();
        qDebug()<<"addnewlistItems"<<itemList.count();

        for(int i = 0;i < itemList.count(); i++)
        {
            qDebug()<<"insert to qml list";
            emit preItemAppended();

            mItems.append({itemList[i].kanjiId,itemList[i].kanji,itemList[i].kunyomi,
                           itemList[i].onyomi,itemList[i].kanjiEnglishName,itemList[i].lastDateAnswered,
                           itemList[i].nextDateToAnswer,itemList[i].correctStreak ,
                           itemList[i].isSelected});

            emit postItemAppended();
        }
        emit fetchedNewKanjiListFromApi();
        //delete apiConnClass;

    });
}

void KanjiList::updateListDatesAfteResult(QList<KanjiListStruct> list)
{
    if(list.isEmpty())
        return;

    for(KanjiListStruct &item : list)
    {
        for(KanjiListStruct &localItem : mItems)
        {
            if(item.kanjiId == localItem.kanjiId)
            {
                localItem.lastDateAnswered = item.lastDateAnswered;
                localItem.nextDateToAnswer = item.nextDateToAnswer;
                localItem.correctStreak = item.correctStreak;
            }
        }
    }
}

void KanjiList::setItemToShowInLearnWindow()
{
    for(KanjiListStruct &item : mItems)
    {
        if(item.isSelected == true)
        {
            qDebug()<<"setItemToShowInLearnWindow";
            m_englishNameTxt = item.kanjiEnglishName;
            qDebug()<<"m_englishNameTxt: "<<m_englishNameTxt;
            m_kanjiTxt = item.kanji;
            m_kunyomiTxt = item.kunyomi;
            m_onyomiTxt = item.onyomi;
            emit englishNameTxtChanged();
            emit kanjiTxtChanged();
            emit kunyomiTxtChanged();
            emit onyomiTxtChanged();
            return;
        }
    }
}
