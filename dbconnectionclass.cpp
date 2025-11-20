#include "dbconnectionclass.h"
#include "qsqlquery.h"
#include <QSqlError>
#include <QCryptographicHash>

DbConnectionClass::DbConnectionClass()
{
    qDebug()<<"DBCONN CONSTRUCTOR";
}

void DbConnectionClass::setupConn()
{

    xmlReader = new XMLReaderClass;
    //readxml if element is not blank fetch it
    initializeSavedPathFile();
    loadDbConfigXmlFile();
    //populateModelList();

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
    if(!db.open())
        qDebug()<<"Database Connection Failed";

    initializeUserInfo();
}

void DbConnectionClass::loadDbConfigXmlFile()
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
        xmlReader->replaceElementVal("Config.xml","filepath",_dbConfigFilePath);
}

void DbConnectionClass::clearFilePathInXML()
{
    xmlReader->replaceElementVal("Config.xml","filepath","");
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

void DbConnectionClass::UpdateDbItems(QList<KanjiQuizStruct> list, QString userIdVal)
{

    qDebug()<<"DB update func called";
    QSqlQuery query;
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
        query.bindValue(":userid", userIdVal);
        if(query.exec())
        {
            qDebug()<<"update executed";
            qDebug()<<"dateAnswered"<<item.dateAnswered;
            qDebug()<<"nextdatetoanswr"<<item.nextDateToAnswer;
            qDebug()<<"userid"<<userIdVal;
        }
    }
}

void DbConnectionClass::UpdateDbItems(QList<VocabQuizStruct> list, QString userIdVal)
{
    qDebug()<<"DB update vocab func called";
    QSqlQuery query;
    query.prepare("UPDATE JapaneseLearningDb.UserVocabDateTable "
                  "SET LastDateAnswered = :lastdateanswered, "
                  "NextDateToAnswer = :nextdatetoanswer, "
                  "CorrectStreak = :correctcounter "
                  "WHERE UserId = :userid && VocabId = :vocabid");

    for(const VocabQuizStruct &item : list)
    {
        query.bindValue(":lastdateanswered", item.dateAnswered.toString("yyyy-MM-dd"));
        query.bindValue(":nextdatetoanswer", item.nextDateToAnswer.toString("yyyy-MM-dd"));
        query.bindValue(":correctcounter", item.correctCounter);
        query.bindValue(":vocabid", item.vocabId);
        query.bindValue(":userid", userIdVal);
        if(query.exec())
        {
            qDebug()<<"update executed";
            qDebug()<<"dateAnswered"<<item.dateAnswered;
            qDebug()<<"nextdatetoanswr"<<item.nextDateToAnswer;
            qDebug()<<"userid"<<userIdVal;
        }
    }
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

void DbConnectionClass::saveUserInfoToXml()
{
    xmlReader->replaceElementVal("Config.xml","uival",userId);
    xmlReader->replaceElementVal("Config.xml","unval",username);
    xmlReader->replaceElementVal("Config.xml","upval",password);
    xmlReader->replaceElementVal("Config.xml","isloggedin","true");
}

void DbConnectionClass::initializeUserInfo()
{
    xmlReader->loadDocument("Config.xml");
    QStringList userInfoList = xmlReader->getSavedUserInfo();
    if(userInfoList.isEmpty())
        return;


    for(const QString &info : std::as_const(userInfoList))
    {
        if(info == "")
            return;
    }

    userId = userInfoList.at(0);
    username = userInfoList.at(1);
    password = userInfoList.at(2);
    qDebug()<<"initialize user info"<<userId<<username<<password;
    loginUser(username,password);
}

void DbConnectionClass::populateModelList(QString userIdVal)
{
    QSqlQuery query;

    query.prepare("SELECT tKanji.KanjiId, Kanji, Kunyomi, Onyomi, KanjiMeaning, LastDateAnswered, NextDateToAnswer, CorrectStreak "
                  "FROM JapaneseLearningDb.KanjiTable as tKanji "
                  "JOIN JapaneseLearningDb.UserDateTable as tDate ON tDate.KanjiId = tKanji.KanjiId "
                  "WHERE tDate.UserId = :userIdVal");

    query.bindValue(":userIdVal", userIdVal);

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
                query.value(7).toString(),//jlptlvl
                query.value(8).toInt(),   //correctstreak
                false
            );

            qDebug()<<query.value(1).toString()<<query.value(2).toString()
                   <<query.value(3).toString()<<query.value(4).toString();
            dbKanjiList.append(kanjiStruct);
        }
    }

    qDebug()<<"insertitems to model";

    //db.close();
}

void DbConnectionClass::populateVocabModelList(QString userIdVal)
{
    QSqlQuery query;

    query.prepare("SELECT tVocab.VocabId, VocabKanji, VocabMeaning, VocabReading, LastDateAnswered, NextDateToAnswer, CorrectStreak "
                  "FROM JapaneseLearningDb.VocabTable as tVocab "
                  "JOIN JapaneseLearningDb.UserVocabDateTable as tDate ON tDate.VocabId = tVocab.VocabId "
                  "WHERE tDate.UserId = :userIdVal");

    query.bindValue(":userIdVal", userIdVal);

    if(query.exec())
    {
        qDebug()<<"populateVocabModelList db query exec successful";
        while(query.next())
        {
            VocabListStruct vocabStruct(
                query.value(0).toString(),//vocabid
                query.value(1).toString(),//vocabkanji
                query.value(2).toString(),//vocabMeaning
                query.value(3).toString(),//vocabreading
                query.value(4).toString(),//lastdateanswered
                query.value(5).toString(),//nextdatetoanswer
                query.value(6).toString(),//jlpt
                query.value(7).toInt(),//correctstreak
                false
                );

            qDebug()<<query.value(1).toString()<<query.value(2).toString()
                     <<query.value(3).toString()<<query.value(4).toString();
            dbVocabList.append(vocabStruct);
        }
    }

    qDebug()<<"insertitems to vocabmodel";

    db.close();
}

bool DbConnectionClass::loginUser(QString usernameVal, QString passwordVal)
{

    qDebug()<<"DB loginuser called";

    QString storePassword = encryptString(passwordVal);

    QSqlQuery query;
    query.prepare("SELECT * FROM JapaneseLearningDb.UserTable "
                  "WHERE  UserName = :username && UserPassword = :password");

    query.bindValue(":username", usernameVal);
    query.bindValue(":password", storePassword);
    if(query.exec())
    {
        if(query.next())
        {
            userId = query.value(1).toString();
            username = query.value(2).toString();
            password = query.value(3).toString();
            saveUserInfoToXml();
            return true;
        }
    }

    return false;
}

void DbConnectionClass::logoutUser()
{
    //clearxml
    xmlReader->replaceElementVal("Config.xml","uival","");
    xmlReader->replaceElementVal("Config.xml","unval","");
    xmlReader->replaceElementVal("Config.xml","upval","");
    xmlReader->replaceElementVal("Config.xml","isloggedin","false");
}

bool DbConnectionClass::insertUser(QString unameVal, QString passwordVal, QString emailVal)
{
    qDebug()<<"DB insertuser called";

    QString storePassword = encryptString(passwordVal);

    QSqlQuery query;

    //Check if the username is unique
    query.prepare("SELECT * FROM JapaneseLearningDb.UserTable "
                  "WHERE UserName COLLATE utf8mb4_bin = :username");
    query.bindValue(":username", unameVal);
    if(query.exec())
    {
        if(query.next())
        {
            return false;
        }
    }

    query.prepare("INSERT INTO JapaneseLearningDb.UserTable(UserName, UserPassword, EmailAddress) "
                  "VALUES(:username, :password, :email)");

    query.bindValue(":username", unameVal);
    query.bindValue(":password", storePassword);
    query.bindValue(":email", emailVal);

    if (!query.exec())
    {
        qDebug() << "Error inserting data:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Data inserted successfully!";

        query.prepare("UPDATE JapaneseLearningDb.UserTable "
                      "SET UserId = CONCAT('USR-', Id) "
                      "WHERE UserName = :username");
        query.bindValue(":username", unameVal);

        if (!query.exec())
        {
            qDebug() << "Error updating userid:" << query.lastError().text();
            return false;
        }
        else
            return true;

    }

    return false;
}

bool DbConnectionClass::insertKanjiItemForUser(QString userIdVal)
{
    QSqlQuery query;
    query.prepare("SELECT KanjiId, Id, UserId FROM JapaneseLearningDb.UserDateTable "
                  "WHERE UserId = :userid "
                  "ORDER BY Id DESC "
                  "LIMIT 1");

    query.bindValue(":userid", userIdVal);

    QString lastKanjiId;
    if (!query.exec())
    {
        qDebug() << "Error retrieving data:" << query.lastError().text();
        return false;
    }
    else
    {
        if(query.next())
        {
            lastKanjiId = query.value(0).toString();
        }
        else
        {
            lastKanjiId = "KI-0";
        }
    }

    QStringList kanjiIdList;
    //get kanjiid number Kj-1
    if(lastKanjiId !="")
    {
        QString newString = lastKanjiId.remove(0,3);
        int counterId = newString.toInt();

        //increment and add to qstringlist
        for(int i = counterId + 1; i <= counterId + 5; i++)
        {
            QString newKanjiId = "KI-" + QString::number(i);
            kanjiIdList.append(newKanjiId);
        }
    }

    //insert values to userdatetable
    query.prepare("INSERT INTO JapaneseLearningDb.UserDateTable(UserId, KanjiId) "
                  "VALUES(:userid, :kanjiid)");

    for(const QString &item : kanjiIdList)
    {
        query.bindValue(":userid", userIdVal);
        query.bindValue(":kanjiid", item);

        if (!query.exec())
        {
            qDebug() << "Error inserting data:" << query.lastError().text();
            return false;
        }
        else
            qDebug() << "insertKanjiItemForUser";
    }

    if(!kanjiIdList.isEmpty())
        addNewItemsToDbKanjiList(kanjiIdList, userIdVal);

    return true;
}

bool DbConnectionClass::insertVocabItemForUser(QString userIdVal)
{
    QSqlQuery query;
    query.prepare("SELECT VocabId, Id, UserId FROM JapaneseLearningDb.UserVocabDateTable "
                  "WHERE UserId = :userid "
                  "ORDER BY Id DESC "
                  "LIMIT 1");

    query.bindValue(":userid", userIdVal);

    QString lastVocabId;
    if (!query.exec())
    {
        qDebug() << "Error retrieving data:" << query.lastError().text();
        return false;
    }
    else
    {
        if(query.next())
        {
            lastVocabId = query.value(0).toString();
        }
        else
        {
            lastVocabId = "VI-0";
        }
    }

    QStringList vocabIdList;
    //get vocabid number VI-1
    if(lastVocabId !="")
    {
        QString newString = lastVocabId.remove(0,3);
        int counterId = newString.toInt();

        //increment and add to qstringlist
        for(int i = counterId + 1; i <= counterId + 5; i++)
        {
            QString newVocabId = "VI-" + QString::number(i);
            vocabIdList.append(newVocabId);
        }
    }

    //insert values to UserVocabDateTable
    query.prepare("INSERT INTO JapaneseLearningDb.UserVocabDateTable(UserId, VocabId) "
                  "VALUES(:userid, :vocabid)");

    for(const QString &item : vocabIdList)
    {
        query.bindValue(":userid", userIdVal);
        query.bindValue(":vocabid", item);

        if (!query.exec())
        {
            qDebug() << "Error inserting data:" << query.lastError().text();
            return false;
        }
        else
            qDebug() << "insertKanjiItemForUser";
    }

    if(!vocabIdList.isEmpty())
        addNewItemsToDbVocabList(vocabIdList, userIdVal);

    return true;
}

void DbConnectionClass::testFunc()
{
    int counterId = 5;

    //increment and add to qstringlist
    for(int i = counterId+1; i <= counterId + 5; i++)
    {
        QString newKanjiId = "KI-" + QString::number(i);
        qDebug()<<"testFunc: "<<newKanjiId;
    }
}

void DbConnectionClass::clearDbKanjiList()
{
    dbKanjiList.clear();
}

void DbConnectionClass::clearDbVocabList()
{
    dbVocabList.clear();
}


QString DbConnectionClass::encryptString(QString stringVal)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(stringVal.toUtf8());
    QByteArray resultHash = hash.result();
    return resultHash.toHex();
}

void DbConnectionClass::addNewItemsToDbKanjiList(QStringList list, QString userIdVal)
{
    QSqlQuery query;
    appendKanjiList.clear();

    qDebug()<<"addNewItemsToDbKanjiList list count: "<<list.count();

    query.prepare("SELECT tKanji.KanjiId, Kanji, Kunyomi, Onyomi, KanjiMeaning, LastDateAnswered, NextDateToAnswer, CorrectStreak "
                  "FROM JapaneseLearningDb.KanjiTable as tKanji "
                  "JOIN JapaneseLearningDb.UserDateTable as tDate ON tDate.KanjiId = tKanji.KanjiId "
                  "WHERE tDate.UserId = :userIdVal && tKanji.KanjiId = :kanjiid");

    for(QString &newId : list)
    {
        query.bindValue(":userIdVal", userIdVal);
        query.bindValue(":kanjiid", newId);
        qDebug()<<"addNewItemsToDbKanjiList newid: "<<newId;
        if(query.exec())
        {
            if(query.next())
            {
                KanjiListStruct kanjiStruct(
                    query.value(0).toString(),//kanjiid
                    query.value(1).toString(),//kanji
                    query.value(2).toString(),//kunyomi
                    query.value(3).toString(),//onyomi
                    query.value(4).toString(),//kanjiMeaning
                    query.value(5).toString(),//lastdateanswered
                    query.value(6).toString(),//nextdatetoanswer
                    query.value(7).toString(),//jlptlvl
                    query.value(8).toInt(),   //correctstreak
                    false
                );
                qDebug()<<query.value(1).toString()<<query.value(2).toString()
                         <<query.value(3).toString()<<query.value(4).toString();
                appendKanjiList.append(kanjiStruct);

                qDebug()<<"addNewItemsToDbKanjiList";
            }
        }
    }
}

void DbConnectionClass::addNewItemsToDbVocabList(QStringList list, QString userIdVal)
{
    QSqlQuery query;
    appendVocabList.clear();

    qDebug()<<"addNewItemsToDbKanjiList list count: "<<list.count();

    query.prepare("SELECT tVocab.VocabId, VocabKanji, VocabMeaning, VocabReading, LastDateAnswered, NextDateToAnswer, CorrectStreak "
                  "FROM JapaneseLearningDb.VocabTable as tVocab "
                  "JOIN JapaneseLearningDb.UserVocabDateTable as tDate ON tDate.VocabId = tVocab.VocabId "
                  "WHERE tDate.UserId = :userIdVal && tVocab.VocabId = :vocabid");

    for(QString &newId : list)
    {
        query.bindValue(":userIdVal", userIdVal);
        query.bindValue(":vocabid", newId);
        qDebug()<<"addNewItemsToDbKanjiList newid: "<<newId;
        if(query.exec())
        {
            if(query.next())
            {
                VocabListStruct vocabStruct(
                    query.value(0).toString(),//vocabid
                    query.value(1).toString(),//vocabkanji
                    query.value(2).toString(),//vocabMeaning
                    query.value(3).toString(),//vocabreading
                    query.value(4).toString(),//lastdateanswered
                    query.value(5).toString(),//nextdatetoanswer
                    query.value(6).toString(),//nextdatetoanswer
                    query.value(7).toInt(),//correctstreak
                    false
                    );

                qDebug()<<query.value(1).toString()<<query.value(2).toString()
                         <<query.value(3).toString()<<query.value(4).toString();
                appendVocabList.append(vocabStruct);
            }
        }
    }
}

