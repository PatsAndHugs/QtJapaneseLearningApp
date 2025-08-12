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

public:
    DbConnectionClass();

    Q_INVOKABLE void setupConn();
    Q_INVOKABLE void loadXmlFile();

    QString getConfigFilePath(){return _dbConfigFilePath;}

    void setConfigFilePath(const QString &configFilePath);

signals:

    void configfilePathChanged();

private:

    QString _dbConfigFilePath;
    XMLReaderClass* xmlReader;
    QSqlDatabase db;
};

#endif // DBCONNECTIONCLASS_H
