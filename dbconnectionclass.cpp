#include "dbconnectionclass.h"

DbConnectionClass::DbConnectionClass()
{
}

void DbConnectionClass::setupConn()
{
    if(xmlReader == nullptr)
        return;

    QString username = xmlReader->getUsername();
    QString password = xmlReader->getPassword();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setConnectOptions("MYSQL_OPT_SSL_MODE=SSL_MODE_DISABLED");
    db.setHostName("database-1.clis4mmic0uk.ap-southeast-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("JapaneseLearningDb");
    db.setUserName(username);
    db.setPassword(password);
}

void DbConnectionClass::loadXmlFile()
{
    if(_dbConfigFilePath !="")
    {
        xmlReader = new XMLReaderClass;
        xmlReader->loadDocument(_dbConfigFilePath);
        qDebug()<<"loaded xml file";
    }
}

void DbConnectionClass::saveFilePathToXml()
{
    xmlReader = new XMLReaderClass;
    //A:/C++Practice/qt/QtJapaneseLearningApp
    if(_dbConfigFilePath != "")
        xmlReader->replaceElementVal("Config.xml",_dbConfigFilePath);
}

void DbConnectionClass::setConfigFilePath(const QString &configFilePath)
{
    QString newString = configFilePath;
    _dbConfigFilePath = newString.remove(0,8);
    emit configfilePathChanged();
}
