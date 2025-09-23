#ifndef DBCONNECTIONCLASS_H
#define DBCONNECTIONCLASS_H

#include <QObject>
#include <xmlreaderclass.h>
#include <qsqldatabase.h>
#include <qqml.h>
#include <kanjilistmodel.h>
#include "kanjilist.h"
#include "kanjiquiz.h"
#include "vocab/vocablist.h"

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

    QList<KanjiListStruct> getAppendKanjiList(){return appendKanjiList;}

    QList<VocabListStruct> getDbVocabList(){return dbVocabList;}
    QList<VocabListStruct> getAppendVocabList(){return appendVocabList;}

    void UpdateDbItems(QList<KanjiQuizStruct> list, QString userIdVal);

    void populateModelList(QString userIdVal);
    void populateVocabModelList(QString userIdVal);
    bool loginUser(QString usernameVal, QString passwordVal);
    Q_INVOKABLE void logoutUser();

    bool insertUser(QString unameVal, QString passwordVal, QString emailVal);

    Q_INVOKABLE bool insertKanjiItemForUser(QString userIdVal);
    Q_INVOKABLE bool insertVocabItemForUser(QString userIdVal);

    Q_INVOKABLE void testFunc();

    void clearDbKanjiList();
    void clearDbVocabList();

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
    QList<VocabListStruct> dbVocabList;

    QString userId;

    QString encryptString(QString stringVal);

    void addNewItemsToDbKanjiList(QStringList list, QString userIdVal);
    QList<KanjiListStruct> appendKanjiList;
    void addNewItemsToDbVocabList(QStringList list, QString userIdVal);
    QList<VocabListStruct> appendVocabList;
};

#endif // DBCONNECTIONCLASS_H
