#include "kanjilistmodel.h"

#include "kanjilist.h"

KanjiListModel::KanjiListModel(QObject *parent)
    :QAbstractListModel(parent)
    , mList(nullptr)
{

}



int KanjiListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant KanjiListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
        return QVariant();

    const KanjiListStruct item = mList->items().at(index.row());
    switch(role){
    case KanjiRole:
        return QVariant(item.kanji);

    case KunyomiRole:
        return QVariant(item.kunyomi);

    case OnyomiRole:
        return QVariant(item.onyomi);

    case KanjiEnglishNameRole:
        return QVariant(item.kanjiEnglishName);

    case JpltLevelRole:
        return QVariant(item.jlptLevel);

    case IsSelectedRole:
        return QVariant(item.isSelected);
    }

    return QVariant();
}

bool KanjiListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    KanjiListStruct item = mList->items().at(index.row());
    switch (role){
    case KanjiRole:
        item.kanji = value.toString();
        break;
    case KunyomiRole:
        item.kunyomi = value.toString();
        break;

    case OnyomiRole:
        item.onyomi = value.toString();
        break;

    case KanjiEnglishNameRole:
        item.kanjiEnglishName = value.toString();
        break;

    case JpltLevelRole:
        item.jlptLevel = value.toString();
        break;

    case IsSelectedRole:
        item.isSelected = value.toBool();
        break;
    }

    if(mList->setItemAt(index.row(), item)){
        emit dataChanged(index, index, QVector<int>() << role);
        qDebug()<<"setdata change";
        return true;
    }
    return false;
}

Qt::ItemFlags KanjiListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}


QHash<int, QByteArray> KanjiListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KanjiRole] = "kanji";
    names[KunyomiRole] = "kunyomi";
    names[OnyomiRole] = "onyomi";
    names[KanjiEnglishNameRole] = "kanjiEnglishName";
    names[JpltLevelRole] = "jpltLevel";
    names[IsSelectedRole] = "isSelected";
    return names;
}


KanjiList *KanjiListModel::list() const
{
    return mList;
}


void KanjiListModel::setList(KanjiList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &KanjiList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &KanjiList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &KanjiList::preItemRemoved, this, [=]() {

            beginRemoveRows(QModelIndex(),0, mList->items().size()-1);

        });

        connect(mList, &KanjiList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

KanjiList *KanjiListModel::selectionlist() const
{
    return mList;
}

void KanjiListModel::updateSelection(KanjiList *list)
{
    beginResetModel();

    mList = list;

    if(mList){
        connect(mList, &KanjiList::postIsSelectedChanged, this, [=]() {
            QList<int> newSelectionList = mList->getSelectionList();
            for(int i = 0 ;i < newSelectionList.count();i++)
            {
                QModelIndex changedIndex = index(newSelectionList[i],0);
                QVector<int> changedRoles;
                changedRoles <<IsSelectedRole << KanjiRole << KanjiEnglishNameRole << OnyomiRole << KunyomiRole << JpltLevelRole;
                emit dataChanged(changedIndex,changedIndex,changedRoles);
                qDebug()<<"updateSelection"<<newSelectionList.count();
                qDebug()<<"current index "<<newSelectionList[i];
            }

        });
    }
    endResetModel();
}

