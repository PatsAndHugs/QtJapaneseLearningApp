#include "kanjilistmodel.h"

#include "kanjilist.h"

KanjiListModel::KanjiListModel(QObject *parent):mList(nullptr){}

int KanjiListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_items.count();
}

QVariant KanjiListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_items.count())
        return QVariant();

    const KanjiItemStruct &item = m_items.at(index.row());
    switch (role)
    {
        case KanjiRole: return item.Kanji;
        case KunyomiRole: return item.Kunyomi;
        case OnyomiRole: return item.Onyomi;
        case KanjiEnglishNameRole: return item.KanjiEnglishName;
        default: return QVariant();
    }
}

QHash<int, QByteArray> KanjiListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KanjiRole] = "kanji";
    roles[KunyomiRole] = "kunyomi";
    roles[OnyomiRole] = "onyomi";
    roles[KanjiEnglishNameRole] = "kanjienglishname";
    return roles;
}

bool KanjiListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    KanjiItemStruct &item = m_items[index.row()];
    if (role == KanjiRole) item.Kanji = value.toString();
    else if (role == KunyomiRole) item.Kunyomi = value.toString();
    else if (role == OnyomiRole) item.Onyomi = value.toString();
    else if (role == KanjiEnglishNameRole) item.KanjiEnglishName = value.toString();
    else return false;

    emit dataChanged(index, index, { role } );
    qDebug()<<"emitted";
    return true;
}

void KanjiListModel::addItem(const KanjiItemStruct &item)
{
    beginResetModel();
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    endInsertRows();

    QModelIndex changedIndex = index(m_items.count()-1, 0);
    QModelIndex startindex = createIndex(0, 0);
    qDebug()<<item.KanjiEnglishName;
    endResetModel();
    emit dataChanged(startindex, changedIndex);

}

Qt::ItemFlags KanjiListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    // Example: All items are enabled, selectable, and editable
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void KanjiListModel::setList(KanjiList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList =list;

    if(mList)
    {
        connect(mList, &KanjiList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &KanjiList::postItemAppended, this, [=]() {
            endInsertRows();
        });
    }
    endResetModel();
}
