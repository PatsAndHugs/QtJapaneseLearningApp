#include "filtervocablistmodel.h"
#include "vocablistmodel.h"

FilterVocabListModel::FilterVocabListModel(QObject *parent)
{
}

void FilterVocabListModel::setSearchText(const QString &text)
{
    if (m_searchText != text) {
        m_searchText = text;
        invalidateFilter(); // Re-evaluate filter when search text changes
        emit searchTextChanged();
    }
}

bool FilterVocabListModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_searchText.isEmpty()) {
        return true; // No filter applied if search text is empty
    }

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    // Assuming you want to search by name and description
    QString vocabReading = sourceModel()->data(index, VocabListModel::VocabReadingRole).toString();
    QString vocabMeaning = sourceModel()->data(index, VocabListModel::VocabMeaningRole).toString();

    return vocabReading.contains(m_searchText, Qt::CaseInsensitive) ||
           vocabMeaning.contains(m_searchText, Qt::CaseInsensitive);
}
