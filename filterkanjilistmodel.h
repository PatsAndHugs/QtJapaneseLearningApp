#ifndef FILTERKANJILISTMODEL_H
#define FILTERKANJILISTMODEL_H

#include <QSortFilterProxyModel>

class FilterKanjiListModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)

public:
    explicit FilterKanjiListModel(QObject *parent = nullptr);

    QString searchText() const {return m_searchText;}
    void setSearchText(const QString &text);

signals:

    void searchTextChanged();

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;
};

#endif // FILTERKANJILISTMODEL_H
