#ifndef APICONNECTIONCLASS_H
#define APICONNECTIONCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "kanjilist.h"

class ApiConnectionClass : public QObject
{
    Q_OBJECT

public:

    explicit ApiConnectionClass(QObject *parent = nullptr);

    void fetchKanjiListForUser();
    QList<KanjiListStruct> getKanjiOutputList(){return kanjiOutputList;}

private:

    QList<KanjiListStruct> kanjiOutputList;
    QJsonObject rootObject;

signals:

    void kanjiOutputListChanged();
};

#endif // APICONNECTIONCLASS_H
