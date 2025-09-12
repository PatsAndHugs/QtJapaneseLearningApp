#ifndef XMLREADERCLASS_H
#define XMLREADERCLASS_H

#include "QtXml"

class XMLReaderClass
{
public:
    XMLReaderClass();

public:

    void loadDocument(QString filePath);
    void replaceElementVal(QString xmlPath, QString tagName, QString newText);
    QString getUsername();
    QString getPassword();
    QString getSavedPathFile();
    QStringList getSavedUserInfo();
    QString getLoggedinStatus();

private:

    QDomElement root;
    QDomDocument document;

    QString readElement(QString tagName);

};

#endif // XMLREADERCLASS_H
