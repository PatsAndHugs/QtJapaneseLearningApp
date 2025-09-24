#include "vocabquizresultmodel.h"

VocabQuizResultModel::VocabQuizResultModel(QObject *parent) {}

int VocabQuizResultModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_dataList.count();
}

QVariant VocabQuizResultModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_dataList.count())
        return QVariant();

    const VocabQuizStruct &data = m_dataList.at(index.row());
    switch(role)
    {
    case VocabIdRole:
        return data.vocabId;

    case IsAnswerCorrectRole:
        return data.isAnswerCorrect;

    case DateAnsweredRole:
        return data.dateAnswered;

    case NextDateToAnswerRole:
        return data.nextDateToAnswer;

    case CorrectCounterRole:
        return data.correctCounter;

    case VocabKanjiRole:
        return data.vocabKanji;

    case VocabMeaningRole:
        return data.vocabMeaning;

    case VocabReadingRole:
        return data.vocabReading;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> VocabQuizResultModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[VocabIdRole] = "vocabId";
    roles[IsAnswerCorrectRole] = "isAnswerCorrect";
    roles[DateAnsweredRole] = "dateAnswered";
    roles[NextDateToAnswerRole] = "nextDateToAnswer";
    roles[CorrectCounterRole] = "correctCounter";
    roles[VocabKanjiRole] = "vocabKanji";
    roles[VocabMeaningRole] = "vocabMeaning";
    roles[VocabReadingRole] = "vocabReading";

    return roles;
}

QList<VocabQuizStruct> VocabQuizResultModel::dataList()
{
    return m_dataList;
}

void VocabQuizResultModel::setDataList(QList<VocabQuizStruct> &data)
{
    beginResetModel();
    m_dataList = data;
    endResetModel();
}
