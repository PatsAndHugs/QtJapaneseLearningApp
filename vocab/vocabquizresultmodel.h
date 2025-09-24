#ifndef VOCABQUIZRESULTMODEL_H
#define VOCABQUIZRESULTMODEL_H

#include "vocabquiz.h"
#include <QAbstractListModel>

Q_MOC_INCLUDE("vocab/vocabquiz.h")

class VocabQuiz;

class VocabQuizResultModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<VocabQuizStruct> dataList READ dataList WRITE setDataList)

public:

    explicit VocabQuizResultModel(QObject *parent = nullptr);

    enum {
        VocabIdRole = Qt::UserRole,
        IsAnswerCorrectRole,
        DateAnsweredRole,
        NextDateToAnswerRole,
        CorrectCounterRole,
        VocabKanjiRole,
        VocabMeaningRole,
        VocabReadingRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;


    QList<VocabQuizStruct> dataList();
    void setDataList(QList<VocabQuizStruct> &data);

private:

    QList<VocabQuizStruct> m_dataList;
};

#endif // VOCABQUIZRESULTMODEL_H
