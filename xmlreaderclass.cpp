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
