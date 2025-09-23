#include "vocablistmodel.h"
#include "vocablist.h"

VocabListModel::VocabListModel(QObject *parent) : QAbstractListModel(parent),
    mList(nullptr)
{

}

int VocabListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant VocabListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
        return QVariant();

    const VocabListStruct item = mList->items().at(index.row());
    switch(role){
    case VocabKanjiRole:
        return QVariant(item.vocabKanji);

    case VocabMeaningRole:
        return QVariant(item.vocabMeaning);

    case VocabReadingRole:
        return QVariant(item.vocabReading);

    case IsSelectedRole:
        return QVariant(item.isSelected);
    }

    return QVariant();
}

bool VocabListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    VocabListStruct item = mList->items().at(index.row());
    switch (role){
    case VocabKanjiRole:
        item.vocabKanji = value.toString();
        break;
    case VocabMeaningRole:
        item.vocabMeaning = value.toString();
        break;

    case VocabReadingRole:
        item.vocabReading = value.toString();
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

Qt::ItemFlags VocabListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> VocabListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[VocabKanjiRole] = "vocabKanji";
    names[VocabMeaningRole] = "vocabMeaning";
    names[VocabReadingRole] = "vocabReading";
    names[IsSelectedRole] = "isSelected";
    return names;
}

VocabList *VocabListModel::list() const
{
    return mList;
}

void VocabListModel::setList(VocabList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &VocabList::preVocabItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
            qDebug()<<"setlist";
        });
        connect(mList, &VocabList::postVocabItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &VocabList::preVocabItemRemoved, this, [=]() {

            beginRemoveRows(QModelIndex(),0, mList->items().size()-1);

        });

        connect(mList, &VocabList::postVocabItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

VocabList *VocabListModel::selectionlist() const
{
    return mList;
}

void VocabListModel::updateSelection(VocabList *list)
{
    beginResetModel();

    mList = list;

    if(mList){
        connect(mList, &VocabList::postVocabIsSelectedChanged, this, [=]() {
            QList<int> newSelectionList = mList->getSelectionList();
            for(int i = 0 ;i < newSelectionList.count();i++)
            {
                QModelIndex changedIndex = index(newSelectionList[i],0);
                QVector<int> changedRoles;
                changedRoles <<IsSelectedRole << VocabKanjiRole << VocabReadingRole << VocabMeaningRole;
                emit dataChanged(changedIndex,changedIndex,changedRoles);
                qDebug()<<"updateSelection"<<newSelectionList.count();
                qDebug()<<"current index "<<newSelectionList[i];
            }

        });
    }
    endResetModel();
}
