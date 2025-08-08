#ifndef XMLREADERCLASS_H
#define XMLREADERCLASS_H

#include "QtXml"
class XMLReaderClass
{
public:
    XMLReaderClass();

public:

    void loadDocument(QString filePath);
    QDomElement root;
    QDomDocument document;
};

#endif // XMLREADERCLASS_H
