#include "xmlreaderclass.h"
#include "QFile"
#include "QXmlStreamWriter"

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
    return readElement("dbconfigusername");
}

QString XMLReaderClass::getPassword()
{
    return readElement("dbconfigpassword");

}

QString XMLReaderClass::getSavedPathFile()
{
    loadDocument("Config.xml");
    return readElement("filepath");
}

QStringList XMLReaderClass::getSavedUserInfo()
{
    QStringList userInfoList;
    //loadDocument("Config.xml");
    userInfoList.append(readElement("uival"));
    userInfoList.append(readElement("unval"));
    userInfoList.append(readElement("upval"));

    return userInfoList;
}

QString XMLReaderClass::getLoggedinStatus()
{
    loadDocument("Config.xml");
    return readElement("isloggedin");
}

QString XMLReaderClass::readElement(QString tagName)
{
    QDomElement childElement = root.firstChildElement(tagName);

    if(!childElement.isNull()){
        return childElement.text();
    }
    return "";
}

void XMLReaderClass::replaceElementVal(QString xmlPath, QString tagName, QString newText)
{
    QFile file(xmlPath);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QDomDocument doc;

    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement repRoot = doc.documentElement();
    QDomElement targetElement = repRoot.firstChildElement(tagName);

    if(!targetElement.isNull())
    {
        QDomNode child = targetElement.firstChild();
        while(!child.isNull())
        {
            QDomNode nextChild = child.nextSibling();
            if(child.isText())
            {
                targetElement.removeChild(child);
                qDebug()<<"replaceElement";
            }

            child = nextChild;
        }
        //Text to save
        QDomText outText = doc.createTextNode(newText);
        targetElement.appendChild(outText);
    }

    QFile outFile(xmlPath);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream stream(&outFile);
    doc.save(stream,4);
    outFile.close();


}
