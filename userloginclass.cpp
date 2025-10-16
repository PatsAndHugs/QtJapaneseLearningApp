#include "userloginclass.h"
#include "xmlreaderclass.h"

UserLoginClass::    UserLoginClass(QObject *parent)
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

void UserLoginClass::setCheckboxState(bool checkboxstateVal)
{
    m_checkboxState = checkboxstateVal;
}

QString UserLoginClass::getSavedUsername()
{
    if(settings.value("username").toString() != "")
        return settings.value("username").toString();
    else
        return m_username;
}

void UserLoginClass::checkLoginResult()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();
    if(m_username != "" && m_password != "")
    {
        ApiConnectionClass *apiConnClass = new ApiConnectionClass;
        apiConnClass->loginUser(newUsername, newPassword);
        QObject::connect(apiConnClass, &ApiConnectionClass::loginResultReceived, this, [=](){
            m_loginResult = apiConnClass->getLoginResult();
            qDebug()<<"loginResultReceived "<<m_loginResult;

            settings.setValue("username", newUsername);
            settings.setValue("userid",apiConnClass->getUserId());
            settings.setValue("loginstate", true);
            settings.sync();
            emit userLoginResultReceived();
            delete apiConnClass;
        });
    }
}

void UserLoginClass::logout()
{
    settings.clear();
}

void UserLoginClass::registerUser()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();
    QString newEmail = m_email.simplified();
    if(m_username != "" && m_password != "" && m_email != "")
    {
        ApiConnectionClass *apiConnClass = new ApiConnectionClass;
        apiConnClass->registerNewUser(newUsername,newPassword,newEmail);
        connect(apiConnClass, &ApiConnectionClass::registerFinished, this, [=](){
            m_registerResult = apiConnClass->getRegisterResult();
            emit registerFinished();
        });
    }
}

