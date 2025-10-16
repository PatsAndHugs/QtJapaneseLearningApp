#ifndef USERLOGINCLASS_H
#define USERLOGINCLASS_H

#include <QObject>
#include <QQmlProperty>
#include <QSettings>

#include "dbconnectionclass.h"
#include "network/apiconnectionclass.h"

class UserLoginClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(bool checkboxState READ checkboxState WRITE setCheckboxState NOTIFY checkboxStateChanged)

public:
    explicit UserLoginClass(QObject *parent = nullptr);


    QString username(){return m_username;}
    void setUsername(QString usernameVal);

    QString password(){return m_password;}
    void setPassword(QString passwordVal);

    QString email(){return m_email;}
    void setEmail(QString emailVal);

    bool checkboxState(){return m_checkboxState;}
    void setCheckboxState(bool checkboxstateVal);

    Q_INVOKABLE QString getSavedUsername();

public slots:

    void checkLoginResult();
    bool getLoginResult(){return m_loginResult;}
    void logout();
    void registerUser();

    bool getRegisterResult(){return m_registerResult;}

signals:

    void usernameChanged();
    void passwordChanged();
    void emailChanged();
    void userLoginResultReceived();
    void registerFinished();
    void checkboxStateChanged();
    void registerWindowNotNeeded();
private:

    QSettings settings;
    DbConnectionClass *dbConnClass;
    QString m_username;
    QString m_password;
    QString m_email;
    bool m_loginResult = false;
    bool m_checkboxState = false;
    bool m_registerResult;

};

#endif // USERLOGINCLASS_H
