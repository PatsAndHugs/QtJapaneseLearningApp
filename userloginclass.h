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

public:
    explicit UserLoginClass(QObject *parent = nullptr);


    QString username(){return m_username;}
    void setUsername(QString usernameVal);

    QString password(){return m_password;}
    void setPassword(QString passwordVal);

public slots:

    bool loginResult();

signals:

    void usernameChanged();
    void passwordChanged();

private:

    DbConnectionClass *dbConnClass;

    QString m_username;
    QString m_password;

};

#endif // USERLOGINCLASS_H
