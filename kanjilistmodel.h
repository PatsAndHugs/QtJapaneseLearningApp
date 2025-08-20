#ifndef KANJILISTMODEL_H
#define KANJILISTMODEL_H

#include <QAbstractListModel>
#include <QList>

struct KanjiItemStruct{
    QString Kanji;
    QString Kunyomi;
    QString Onyomi;
    QString KanjiEnglishName;

    KanjiItemStruct(QString valKanji,QString valKunyomi,QString valOnyomi,QString valEnglishName)
    {
        Kanji = valKanji;
        Kunyomi = valKunyomi;
        Onyomi = valOnyomi;
        KanjiEnglishName = valEnglishName;
    }
};

class KanjiListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MyRoles{
        KanjiRole = Qt::UserRole +1,
        KunyomiRole,
        OnyomiRole,
        KanjiEnglishNameRole

    };
    explicit KanjiListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addItem(const KanjiItemStruct& item);
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QList<KanjiItemStruct> m_items;
};

#endif // KANJILISTMODEL_H
