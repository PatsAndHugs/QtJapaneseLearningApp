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

    file.close();

    root = document.firstChildElement();
}

QString XMLReaderClass::getUsername()
{
    return readElement(root,"dbconfigusername","username");
}

QString XMLReaderClass::getPassword()
{
    return readElement(root,"dbconfigpassword","password");

}

QString XMLReaderClass::readElement(QDomElement rootelem, QString tagName, QString attribute)
{
    QDomElement childElement = root.firstChildElement(tagName);

    if(!childElement.isNull()){
        return childElement.text();
    }
    return "";
}
