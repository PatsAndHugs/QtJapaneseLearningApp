#include "dbconnectionclass.h"

DbConnectionClass::DbConnectionClass()
{
    xmlReader = new XMLReaderClass;
    //readxml if element is not blank fetch it
    initializeSavedPathFile();
    _model = new KanjiListModel;
    insertItemsToModel();
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
        xmlReader->loadDocument(_dbConfigFilePath);
        qDebug()<<"loaded xml file";
    }
}

void DbConnectionClass::saveFilePathToXml()
{
    //A:/C++Practice/qt/QtJapaneseLearningApp
    if(_dbConfigFilePath != "")
        xmlReader->replaceElementVal("Config.xml",_dbConfigFilePath);
}

void DbConnectionClass::clearFilePathInXML()
{
    xmlReader->replaceElementVal("Config.xml","");
}

void DbConnectionClass::setConfigFilePath(const QString &configFilePath)
{
    QString newString = configFilePath;
    _dbConfigFilePath = newString.remove(0,8);
    emit configfilePathChanged();
}

void DbConnectionClass::setHasSavedPathFile(const bool &bState)
{
    bHasSavedPathFile = bState;
}

void DbConnectionClass::initializeSavedPathFile()
{
    QString savedPathFile = xmlReader->getSavedPathFile();
    if(savedPathFile == "")
    {
        bHasSavedPathFile = false;
        return;
    }
    else
    {
        _dbConfigFilePath = savedPathFile;
        bHasSavedPathFile = true;
    }
}

void DbConnectionClass::insertItemsToModel()
{
    KanjiItemStruct kanjiStruct("今","いま","none","Today");
    KanjiItemStruct kanjiStruct2("目","め","モク","Eye");
    _model->addItem(kanjiStruct);
    _model->addItem(kanjiStruct2);
}
