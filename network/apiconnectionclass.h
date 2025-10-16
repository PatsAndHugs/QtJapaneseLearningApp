#ifndef APICONNECTIONCLASS_H
#define APICONNECTIONCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>

#include "kanjilist.h"

class ApiConnectionClass : public QObject
{
    Q_OBJECT

public:

    explicit ApiConnectionClass(QObject *parent = nullptr);

    void fetchKanjiListForUser();
    void fetchAdditionalKanjiListForUser();
    QList<KanjiListStruct> getKanjiOutputList(){return kanjiOutputList;}
    void loginUser(QString usernameVal, QString passwordVal);
    bool getLoginResult(){return m_loginResult;}
    QString getUserId(){return m_userId;}

    void registerNewUser(QString usernameVal, QString passwordVal, QString emailVal);
    bool getRegisterResult(){return m_registerResult;}

    QList<KanjiListStruct> getNewKanjiListToAdd(){return newKanjiListToadd;}

private:

    QSettings settings;
    QList<KanjiListStruct> kanjiOutputList;
    QJsonObject rootObject;
    void insertNewKanjiForUser(QJsonArray arrayToInsert);
    QString encryptString(QString stringVal);
    bool m_loginResult;
    bool m_registerResult = false;
    QString m_userId;
    void insertNewUser(QJsonObject userDataVal);

    void addNewItemsToKanjiList();
    QList<KanjiListStruct> newKanjiListToadd;
    std::unique_ptr<QNetworkAccessManager> manager;

signals:

    void kanjiOutputListChanged();
    void loginResultReceived();
    void registerFinished();
    void newKanjiListChanged();

};

#endif // APICONNECTIONCLASS_H
