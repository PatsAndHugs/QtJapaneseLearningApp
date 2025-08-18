#include "kanjilistmodel.h"



KanjiListModel::KanjiListModel(QObject *parent){}

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
    roles[KanjiEnglishNameRole] = "kanjienglishrole";
    return roles;
}

void KanjiListModel::addItem(const KanjiItemStruct &item)
{
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    endInsertRows();
}
