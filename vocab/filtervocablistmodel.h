#ifndef FILTERVOCABLISTMODEL_H
#define FILTERVOCABLISTMODEL_H

#include <QSortFilterProxyModel>

class FilterVocabListModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)

public:
    explicit FilterVocabListModel(QObject *parent = nullptr);

    QString searchText() const {return m_searchText;}
    void setSearchText(const QString &text);

signals:

    void searchTextChanged();

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;

};

#endif // FILTERVOCABLISTMODEL_H
