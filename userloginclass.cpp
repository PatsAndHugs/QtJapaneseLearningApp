#include "userloginclass.h"
#include "xmlreaderclass.h"

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

void UserLoginClass::setEmail(QString emailVal)
{
    m_email = emailVal;
}

bool UserLoginClass::loginResult()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();

    if(m_username != "" && m_password != "")
        return dbConnClass->loginUser(newUsername, newPassword);

    return false;
}

void UserLoginClass::logout()
{
    m_username = "";
    m_password = "";
}

bool UserLoginClass::registerUser()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();
    QString newEmail = m_email.simplified();

    if(m_username != "" && m_password != "" && m_email != "")
        return dbConnClass->insertUser(newUsername, newPassword, newEmail);

    return false;
}

bool UserLoginClass::getLoginStatus()
{
    XMLReaderClass *xmlReader = new XMLReaderClass;

    if(xmlReader->getLoggedinStatus() == "true")
        return true;
    else
        return false;
}

