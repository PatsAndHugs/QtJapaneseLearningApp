#include "xmlreaderclass.h"

XMLReaderClass::XMLReaderClass() {}

void XMLReaderClass::loadDocument(QString filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Failed to open file for reading";
        return;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document";
            return;
        }
        file.close();
        qDebug()<<"Finished";
    }

    root = document.firstChildElement();
}

QString XMLReaderClass::getUsername()
{
    return readElement(root,"dbsetting","username");
}

QString XMLReaderClass::getPassword()
{
    return readElement(root,"dbsetting","password");

}

QString XMLReaderClass::readElement(QDomElement rootelem, QString tagName, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagName);
    QString elementResult;
    QDomNode itemNode = items.at(0);
    if(itemNode.isElement())
    {
        QDomElement itemElement = itemNode.toElement();
        return itemElement.attribute(attribute);
    }
    return "";
}
