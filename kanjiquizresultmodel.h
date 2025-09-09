#ifndef KANJIQUIZRESULTMODEL_H
#define KANJIQUIZRESULTMODEL_H

#include "kanjiquiz.h"
#include <QAbstractListModel>

Q_MOC_INCLUDE("kanjiquiz.h")

class KanjiQuiz;

class KanjiQuizResultModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<KanjiQuizStruct> dataList READ dataList WRITE setDataList)
public:

    explicit KanjiQuizResultModel(QObject *parent = nullptr);

    enum {
        KanjiIdRole = Qt::UserRole,
        IsAnswerCorrectRole,
        DateAnsweredRole,
        NextDateToAnswerRole,
        CorrectCounterRole,
        KanjiRole,
        OnyomiRole,
        KunyomiRole,
        KanjiEnglishMeaning
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;


    QList<KanjiQuizStruct> dataList();
    void setDataList(QList<KanjiQuizStruct> &data);

private:

    QList<KanjiQuizStruct> m_dataList;

};

#endif // KANJIQUIZRESULTMODEL_H
