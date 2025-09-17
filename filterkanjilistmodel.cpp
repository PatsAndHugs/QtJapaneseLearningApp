#include "filterkanjilistmodel.h"
#include "kanjilistmodel.h"

FilterKanjiListModel::FilterKanjiListModel(QObject *parent) {}

void FilterKanjiListModel::setSearchText(const QString &text)
{
    if (m_searchText != text) {
        m_searchText = text;
        invalidateFilter(); // Re-evaluate filter when search text changes
        emit searchTextChanged();
    }
}

bool FilterKanjiListModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_searchText.isEmpty()) {
        return true; // No filter applied if search text is empty
    }

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    // Assuming you want to search by name and description
    QString kanji = sourceModel()->data(index, KanjiListModel::KanjiRole).toString();
    QString englishName = sourceModel()->data(index, KanjiListModel::KanjiEnglishNameRole).toString();

    return kanji.contains(m_searchText, Qt::CaseInsensitive) ||
           englishName.contains(m_searchText, Qt::CaseInsensitive);
}
