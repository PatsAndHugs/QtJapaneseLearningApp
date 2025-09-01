#include "dbconnectionclass.h"
#include "qsqlquery.h"

DbConnectionClass::DbConnectionClass()
{
    xmlReader = new XMLReaderClass;
    //readxml if element is not blank fetch it
    initializeSavedPathFile();
    loadXmlFile();
    //setupConn();
    insertItemsToModel();
}

void DbConnectionClass::setupConn()
{
    if(xmlReader == nullptr)
        return;

    username = xmlReader->getUsername();
    password = xmlReader->getPassword();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setConnectOptions("MYSQL_OPT_SSL_MODE=SSL_MODE_DISABLED");
    db.setHostName("database-1.clis4mmic0uk.ap-southeast-2.rds.amazonaws.com");
    db.setPort(3306);
    db.setDatabaseName("JapaneseLearningDb");
    db.setUserName(username);
    db.setPassword(password);
    qDebug()<<username<<" "<<password;
}

void DbConnectionClass::loadXmlFile()
{
    if(_dbConfigFilePath !="")
    {    
        xmlReader->loadDocument(_dbConfigFilePath);
        qDebug()<<"dbconnclass loaded xml file";
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
    if(db.open())
    {
        qDebug()<<"db connection successful";
        QSqlQuery query(db);
        query.prepare("Select KanjiId, Kanji, Kunyomi, Onyomi, KanjiMeaning "
                      "FROM JapaneseLearningDb.KanjiTable");
        if(query.exec())
        {
            qDebug()<<"db query exec successful";
            while(query.next())
            {

                KanjiListStruct kanjiStruct(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString(),
                    query.value(4).toString(),
                    false
                );

                qDebug()<<query.value(1).toString()<<query.value(2).toString()
                       <<query.value(3).toString()<<query.value(4).toString();
                dbKanjiList.append(kanjiStruct);
            }
        }
    }

    qDebug()<<"insertitems to model";

    db.close();
}
