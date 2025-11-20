#include "vocabdetailsmodel.h"

VocabDetailsModel::VocabDetailsModel(QObject *parent) : QAbstractListModel(parent) {}

int VocabDetailsModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || m_list.isEmpty())
        return 0;

    return m_list.count();
}

QVariant VocabDetailsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || m_list.isEmpty())
        return QVariant();

    const VocabDetailsStruct item = m_list.at(index.row());
    switch(role){
    case WordTypeRole:
        return QVariant(item.wordType);
    case VocabMeaningRole:
        return QVariant(item.vocabMeaning);
    }

    return QVariant();
}

bool VocabDetailsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_list.isEmpty())
        return false;

    VocabDetailsStruct item = m_list.at(index.row());

    switch(role){
    case WordTypeRole:
        item.wordType = value.toString();
        break;

    case VocabMeaningRole:
        item.vocabMeaning = value.toString();
        break;
    }

    return false;

}

Qt::ItemFlags VocabDetailsModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> VocabDetailsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[WordTypeRole] = "wordType";
    names[VocabMeaningRole] = "vocabMeaning";

    return names;
}

void VocabDetailsModel::setList(QList<VocabDetailsStruct> listVal)
{
    beginResetModel();

    m_list = listVal;

    for(VocabDetailsStruct item : m_list)
    {
        const int index = m_list.count();
        beginInsertRows(QModelIndex(), index, index);
        qDebug()<<"setlist insertrows";

        endInsertRows();
    }
    endResetModel();
}
