#ifndef KANJILISTMODEL_H
#define KANJILISTMODEL_H

#include <QAbstractListModel>
//#include <QList>

Q_MOC_INCLUDE("kanjilist.h")

class KanjiList;

class KanjiListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(KanjiList *list READ list WRITE setList);
    Q_PROPERTY(KanjiList *selectionlist READ selectionlist WRITE updateSelection)

public:
    explicit KanjiListModel(QObject *parent = nullptr);

    enum {
        KanjiRole = Qt::UserRole,
        KunyomiRole,
        OnyomiRole,
        KanjiEnglishNameRole,
        IsSelectedRole
    };


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    KanjiList *list() const;
    void setList(KanjiList *list);

    KanjiList *selectionlist() const;
    void updateSelection(KanjiList *list);

private:
    KanjiList *mList;
};

#endif // KANJILISTMODEL_H
