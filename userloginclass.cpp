#include "userloginclass.h"

UserLoginClass::UserLoginClass(QObject *parent)
{
    initBarGraphValues();
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

bool UserLoginClass::getSavedLoginState()
{
    return settings.value("loginstate").toBool();
}

void UserLoginClass::initBarGraphValues()
{
    m_barValues<<settings.value("lastdatecount").toInt()
                <<settings.value("secondlastdatecount").toInt()
                <<settings.value("thirdlastdatecount").toInt();
    m_barValues<<settings.value("lastdate").toString()
                <<settings.value("secondlastdate").toString()
                <<settings.value("thirdlastdate").toString();
}

void UserLoginClass::checkLoginResult()
{
    QString newUsername = m_username.simplified();
    QString newPassword = m_password.simplified();
    if(m_username != "" && m_password != "")
    {
        std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
        apiConnClass->loginUser(newUsername, newPassword);

        QEventLoop loop;
        connect(apiConnClass.get(), &ApiConnectionClass::loginResultReceived, &loop, &QEventLoop::quit);

        QObject::connect(apiConnClass.get(), &ApiConnectionClass::loginResultReceived, this, [&](){
            m_loginResult = apiConnClass->getLoginResult();
            qDebug()<<"loginResultReceived "<<m_loginResult;

            settings.setValue("username", newUsername);
            settings.setValue("userid",apiConnClass->getUserId());
            settings.setValue("loginstate", true);
            settings.sync();
            emit userLoginResultReceived();
        });

        loop.exec();
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
        std::unique_ptr<ApiConnectionClass> apiConnClass = std::make_unique<ApiConnectionClass>();
        apiConnClass->registerNewUser(newUsername,newPassword,newEmail);

        QEventLoop loop;
        connect(apiConnClass.get(), &ApiConnectionClass::registerFinished, &loop, &QEventLoop::quit);

        connect(apiConnClass.get(), &ApiConnectionClass::registerFinished, this, [&](){
            m_registerResult = apiConnClass->getRegisterResult();
            emit registerFinished();
        });
        loop.exec();
    }
}


