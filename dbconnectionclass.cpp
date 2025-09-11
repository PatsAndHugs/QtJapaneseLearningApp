#include "dbconnectionclass.h"
#include "qsqlquery.h"

DbConnectionClass::DbConnectionClass()
{
    xmlReader = new XMLReaderClass;
    //readxml if element is not blank fetch it
    initializeSavedPathFile();
    loadXmlFile();
    setupConn(); //uncomment to connect to db
    //populateModelList();
    qDebug()<<"DBCONN CONSTRUCTOR";
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

void DbConnectionClass::UpdateDbItems(QList<KanjiQuizStruct> list)
{
    if(db.open())
    {
        qDebug()<<"DB update func called";
        QSqlQuery query(db);
        query.prepare("UPDATE JapaneseLearningDb.UserDateTable "
                      "SET LastDateAnswered = :lastdateanswered, "
                      "NextDateToAnswer = :nextdatetoanswer, "
                      "CorrectStreak = :correctcounter "
                      "WHERE UserId = :userid && KanjiId = :kanjiid");

        for(const KanjiQuizStruct &item : list)
        {
            query.bindValue(":lastdateanswered", item.dateAnswered.toString("yyyy-MM-dd"));
            query.bindValue(":nextdatetoanswer", item.nextDateToAnswer.toString("yyyy-MM-dd"));
            query.bindValue(":correctcounter", item.correctCounter);
            query.bindValue(":kanjiid", item.kanjiId);
            query.bindValue(":userid", UserId);
            if(query.exec())
                qDebug()<<"update executed";
        }
    }

    db.close();
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

void DbConnectionClass::populateModelList()
{
    if(db.open())
    {
        qDebug()<<"db connection successful";
        QSqlQuery query(db);

        query.prepare("SELECT tKanji.KanjiId, Kanji, Kunyomi, Onyomi, KanjiMeaning, LastDateAnswered, NextDateToAnswer, CorrectStreak "
                      "FROM JapaneseLearningDb.KanjiTable as tKanji "
                      "JOIN JapaneseLearningDb.UserDateTable as tDate ON tDate.KanjiId = tKanji.KanjiId "
                      "WHERE tDate.UserId = :userIdVal");

        query.bindValue(":userIdVal", UserId);

        if(query.exec())
        {
            qDebug()<<"db query exec successful";
            while(query.next())
            {

                KanjiListStruct kanjiStruct(
                    query.value(0).toString(),//kanjiid
                    query.value(1).toString(),//kanji
                    query.value(2).toString(),//kunyomi
                    query.value(3).toString(),//onyomi
                    query.value(4).toString(),//kanjiMeaning
                    query.value(5).toString(),//lastdateanswered
                    query.value(6).toString(),//nextdatetoanswer
                    query.value(7).toInt(),   //correctstreak
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

bool DbConnectionClass::loginUser(QString usernameVal, QString passwordVal)
{
    if(db.open())
    {
        qDebug()<<"DB loginuser called";
        QSqlQuery query(db);
        query.prepare("SELECT * FROM JapaneseLearningDb.UserTable "
                      "WHERE  UserName = :username && UserPassword = :password");

        query.bindValue(":username", usernameVal);
        query.bindValue(":password", passwordVal);
        if(query.exec())
        {
            if(query.next())
            {
                UserId = query.value(1).toString();
                qDebug()<<"USERID "<<UserId;
                return true;
            }
        }
    }

    return false;
}


