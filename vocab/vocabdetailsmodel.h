#ifndef VOCABDETAILSMODEL_H
#define VOCABDETAILSMODEL_H

#include <QAbstractListModel>

#include "vocablist.h"

class VocabDetailsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<VocabDetailsStruct> list READ list WRITE setList);
public:
    explicit VocabDetailsModel(QObject* parent = nullptr);

    enum{
        WordTypeRole = Qt::UserRole,
        VocabMeaningRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    QList<VocabDetailsStruct> list() const{return m_list;}
    void setList(QList<VocabDetailsStruct> listVal);

private:

    QList<VocabDetailsStruct> m_list;
};

#endif // VOCABDETAILSMODEL_H
