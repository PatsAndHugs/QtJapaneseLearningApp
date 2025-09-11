#include "userloginclass.h"


UserLoginClass::UserLoginClass(QObject *parent)
{
    dbConnClass = new DbConnectionClass;
}

void UserLoginClass::setUsername(QString usernameVal)
{
    m_username = usernameVal;
}

void UserLoginClass::setPassword(QString passwordVal)
{
    m_password = passwordVal;
}

bool UserLoginClass::loginResult()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();

    if(m_username != "" && m_password != "")
        return dbConnClass->loginUser(newUsername, newPassword);

    return false;
}

