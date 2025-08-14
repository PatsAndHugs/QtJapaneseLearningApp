#ifndef DBCONNECTIONCLASS_H
#define DBCONNECTIONCLASS_H

#include <QObject>
#include <xmlreaderclass.h>
#include <qsqldatabase.h>
#include <qqml.h>

class DbConnectionClass : public QObject
{

    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString configFilePath READ getConfigFilePath WRITE setConfigFilePath NOTIFY configfilePathChanged)
    Q_PROPERTY(bool bHasSavedPathFile READ getHasSavedPathFile WRITE setHasSavedPathFile NOTIFY hasSavedPathFileStateChanged)

public:
    DbConnectionClass();

    Q_INVOKABLE void setupConn();
    Q_INVOKABLE void loadXmlFile();
    Q_INVOKABLE void saveFilePathToXml();
    Q_INVOKABLE void clearFilePathInXML();

    QString getConfigFilePath(){return _dbConfigFilePath;}
    void setConfigFilePath(const QString &configFilePath);

    bool getHasSavedPathFile(){return bHasSavedPathFile;}
    void setHasSavedPathFile(const bool &bState);

signals:

    void configfilePathChanged();
    void hasSavedPathFileStateChanged();

private:

    QString _dbConfigFilePath;
    XMLReaderClass* xmlReader;
    QSqlDatabase db;
    void initializeSavedPathFile();
    bool bHasSavedPathFile;
};

#endif // DBCONNECTIONCLASS_H
