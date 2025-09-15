#ifndef USERLOGINCLASS_H
#define USERLOGINCLASS_H

#include <QObject>
#include <QQmlProperty>
#include "dbconnectionclass.h"

class UserLoginClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)

public:
    explicit UserLoginClass(QObject *parent = nullptr);


    QString username(){return m_username;}
    void setUsername(QString usernameVal);

    QString password(){return m_password;}
    void setPassword(QString passwordVal);

    QString email(){return m_email;}
    void setEmail(QString emailVal);

public slots:

    bool loginResult();
    void logout();
    bool registerUser();
    bool getLoginStatus();

signals:

    void usernameChanged();
    void passwordChanged();
    void emailChanged();

private:

    DbConnectionClass *dbConnClass;

    QString m_username;
    QString m_password;
    QString m_email;

};

#endif // USERLOGINCLASS_H
