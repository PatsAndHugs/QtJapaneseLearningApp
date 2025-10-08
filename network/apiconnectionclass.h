#ifndef APICONNECTIONCLASS_H
#define APICONNECTIONCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ApiConnectionClass : public QObject
{
    Q_OBJECT

public:

    explicit ApiConnectionClass(QObject *parent = nullptr);
};

#endif // APICONNECTIONCLASS_H
