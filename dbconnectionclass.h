#ifndef DBCONNECTIONCLASS_H
#define DBCONNECTIONCLASS_H

#include <QObject>
#include <xmlreaderclass.h>
#include <qsqldatabase.h>
#include <qqml.h>
#include <kanjilistmodel.h>
#include "kanjilist.h"
#include "kanjiquiz.h"

class DbConnectionClass : public QObject
{

    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString configFilePath READ getConfigFilePath WRITE setConfigFilePath NOTIFY configfilePathChanged)
    Q_PROPERTY(bool bHasSavedPathFile READ getHasSavedPathFile WRITE setHasSavedPathFile NOTIFY hasSavedPathFileStateChanged)

public:
    DbConnectionClass();

    Q_INVOKABLE void setupConn();
    Q_INVOKABLE void loadDbConfigXmlFile();
    Q_INVOKABLE void saveFilePathToXml();
    Q_INVOKABLE void clearFilePathInXML();

    QString getConfigFilePath(){return _dbConfigFilePath;}
    void setConfigFilePath(const QString &configFilePath);

    bool getHasSavedPathFile(){return bHasSavedPathFile;}
    void setHasSavedPathFile(const bool &bState);
    Q_INVOKABLE KanjiListModel* getModel(){return _model;}

    QList<KanjiListStruct> getDbKanjiList(){return dbKanjiList;}

    void UpdateDbItems(QList<KanjiQuizStruct> list);

    void populateModelList(QString userIdVal);
    bool loginUser(QString usernameVal, QString passwordVal);
    Q_INVOKABLE void logoutUser();

    bool insertUser(QString unameVal, QString passwordVal, QString emailVal);

signals:

    void configfilePathChanged();
    void hasSavedPathFileStateChanged();

private:

    KanjiListModel* _model;
    QString _dbConfigFilePath;
    XMLReaderClass* xmlReader;
    QSqlDatabase db;
    void initializeSavedPathFile();
    bool bHasSavedPathFile;
    void saveUserInfoToXml();
    void initializeUserInfo();

    QString username;
    QString password;

    QList<KanjiListStruct> dbKanjiList;
    QString userId;

    QString encryptString(QString stringVal);
};

#endif // DBCONNECTIONCLASS_H
