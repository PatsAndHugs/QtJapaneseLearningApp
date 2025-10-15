#include "userloginclass.h"
#include "xmlreaderclass.h"

UserLoginClass::UserLoginClass(QObject *parent)
{
    dbConnClass = new DbConnectionClass;
    apiConnClass = new ApiConnectionClass;
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

void UserLoginClass::checkLoginResult()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();
    if(m_username != "" && m_password != "")
    {
        apiConnClass->loginUser(newUsername, newPassword);
        QObject::connect(apiConnClass, &ApiConnectionClass::loginResultReceived, this, [=](){
            m_loginResult = apiConnClass->getLoginResult();
            emit userLoginResultReceived();
            qDebug()<<"loginResultReceived "<<m_loginResult;
            if(m_checkboxState)
            {
                settings.setValue("username", newUsername);
                settings.setValue("userid",apiConnClass->getUserId());
                settings.setValue("loginstate", true);
            }
            else
                settings.clear();

        });
        //connect(apiConnClass, &ApiConnectionClass::loginResultReceived, this, &UserLoginClass::userLoginResultReceived);
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
        apiConnClass->registerNewUser(newUsername,newPassword,newEmail);
        connect(apiConnClass, &ApiConnectionClass::registerFinished, this, [=](){
            m_registerResult = apiConnClass->getRegisterResult();
            emit registerFinished();
        });
    }
}

bool UserLoginClass::getLoginStatus()
{
    XMLReaderClass *xmlReader = new XMLReaderClass;

    if(xmlReader->getLoggedinStatus() == "true")
        return true;
    else
        return false;
}

QString UserLoginClass::getUsername()
{
    XMLReaderClass *xmlReader = new XMLReaderClass;
    xmlReader->loadDocument("Config.xml");

    return xmlReader->getSavedUserInfo().at(1);
}

