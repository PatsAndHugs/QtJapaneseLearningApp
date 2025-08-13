#ifndef XMLREADERCLASS_H
#define XMLREADERCLASS_H

#include "QtXml"

class XMLReaderClass
{
public:
    XMLReaderClass();

public:

    void loadDocument(QString filePath);

    QString getUsername();
    QString getPassword();


private:

    QDomElement root;
    QDomDocument document;

    QString readElement(QDomElement rootelem, QString tagName, QString attribute);

    void replaceElementVal(QString filePath);
};

#endif // XMLREADERCLASS_H
