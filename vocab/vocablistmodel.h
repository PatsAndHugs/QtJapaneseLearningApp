#ifndef VOCABLISTMODEL_H
#define VOCABLISTMODEL_H

#include <QAbstractListModel>

Q_MOC_INCLUDE("vocab/vocablist.h")

class VocabList;

class VocabListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(VocabList *list READ list WRITE setList);
    Q_PROPERTY(VocabList *selectionlist READ selectionlist WRITE updateSelection)

public:
    explicit VocabListModel(QObject *parent = nullptr);

    enum{
        VocabKanjiRole = Qt::UserRole,
        VocabMeaningRole,
        VocabReadingRole,
        JlptLevelRole,
        IsSelectedRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    VocabList *list() const;
    void setList(VocabList *list);

    VocabList *selectionlist() const;
    void updateSelection(VocabList *list);

private:
    VocabList *mList;
};

#endif // VOCABLISTMODEL_H
