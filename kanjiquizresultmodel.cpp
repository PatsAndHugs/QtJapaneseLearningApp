#include "kanjiquizresultmodel.h"

KanjiQuizResultModel::KanjiQuizResultModel(QObject *parent) {}

int KanjiQuizResultModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_dataList.count();
}

QVariant KanjiQuizResultModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_dataList.count())
        return QVariant();

    const KanjiQuizStruct &data = m_dataList.at(index.row());
    switch(role)
    {
        case KanjiIdRole:
            return data.kaniId;

        case IsAnswerCorrectRole:
            return data.isAnswerCorrect;

        case DateAnsweredRole:
            return data.dateAnswered;

        case NextDateToAnswerRole:
            return data.nextDateToAnswer;

        case CorrectCounterRole:
            return data.correctCounter;

        case KanjiRole:
            return data.kanji;

        case OnyomiRole:
            return data.onyomi;

        case KunyomiRole:
            return data.kunyomi;

        case KanjiEnglishMeaning:
            return data.kanjiEnglishMeaning;

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> KanjiQuizResultModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[KanjiIdRole] = "kanjiId";
    roles[IsAnswerCorrectRole] = "isAnswerCorrect";
    roles[DateAnsweredRole] = "dateAnswered";
    roles[NextDateToAnswerRole] = "nextDateToAnswer";
    roles[CorrectCounterRole] = "correctCounter";
    roles[KanjiRole] = "kanji";
    roles[OnyomiRole] = "onyomi";
    roles[KunyomiRole] = "kunyomi";
    roles[KanjiEnglishMeaning] = "kanjiEnglishMeaning";

    return roles;
}

QList<KanjiQuizStruct> KanjiQuizResultModel::dataList()
{
    return m_dataList;
}

void KanjiQuizResultModel::setDataList(QList<KanjiQuizStruct> &data)
{
    beginResetModel();
    m_dataList = data;
    endResetModel();
}
