#include "apiconnectionclass.h"
#include "QList"

ApiConnectionClass::ApiConnectionClass(QObject *parent) {
    qDebug()<<"APi Constructor";
}

void ApiConnectionClass::fetchKanjiListForUser()
{
    //clears everything each call
    //kanjiOutputList.clear();

    //query
    QJsonObject userData;
    //CHANGE LATER
    userData["userid"] = "USR-1";
    QJsonDocument userDoc(userData);
    QByteArray userJsonData = userDoc.toJson();

    QUrl serviceUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/kanji_resource/per_user"); // Replace with your actual login endpoint
    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, userJsonData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            // Process the responseData (e.g., parse JSON)
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                rootObject = jsonDoc.object();
                QString jsonText;
                for (QJsonObject::iterator it = rootObject.begin(); it != rootObject.end(); ++it) {
                    if(it.key() == "body")
                    {
                        jsonText = it.value().toString();
                        QByteArray jsonData = jsonText.toUtf8();
                        QJsonDocument doc = QJsonDocument::fromJson(jsonData);

                        if(!doc.isNull() && doc.isArray())
                        {
                            QJsonArray jsonArray = doc.array();
                            for (const QJsonValue &value : std::as_const(jsonArray)) {
                                KanjiListStruct listStruct(
                                    value["KanjiId"].toString(),
                                    value["Kanji"].toString(),
                                    value["Kunyomi"].toString(),
                                    value["Onyomi"].toString(),
                                    value["KanjiMeaning"].toString(),
                                    value["LastDateAnswered"].toString(),
                                    value["NextDateAnswered"].toString(),
                                    value["CorrectStreak"].toInt(),
                                    false
                                    );
                                kanjiOutputList.append(listStruct);
                            }
                            emit kanjiOutputListChanged();
                            //reply->deleteLater();
                            reply->abort();
                        }
                    }
                }
            }
        }
        else{
            qDebug() << "Error: " << reply->errorString();
        }
        //reply->deleteLater();
        reply->abort();
    });
}

void ApiConnectionClass::fetchAdditionalKanjiListForUser()
{
    //query
    QJsonObject userData;
    //CHANGE LATER
    userData["userid"] = "USR-2";
    QJsonDocument userDoc(userData);
    QByteArray userJsonData = userDoc.toJson();

    //api query for last kanji
    QUrl serviceUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/kanji_resource/per_user/insert_kanji");
    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, userJsonData);
    QString lastKanjiId;

    QStringList kanjiIdList;
    connect(reply, &QNetworkReply::finished, this, [=, &lastKanjiId, &kanjiIdList]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            // Process the responseData (e.g., parse JSON)
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                //QString jsonText;
                rootObject = jsonDoc.object();
                lastKanjiId = rootObject.value("body").toString();
                qDebug()<<"LastKanji"<<lastKanjiId;
                reply->abort();

                //get kanjiid number Kj-1
                if(lastKanjiId !="")
                {
                    QString newString = lastKanjiId.remove(0,4);
                    newString = newString.remove(1,2);
                    int counterId = newString.toInt();
                    qDebug()<<"newString"<<newString;
                    //increment and add to qstringlist
                    for(int i = counterId + 1; i <= counterId + 5; i++)
                    {
                        QString newKanjiId = "KI-" + QString::number(i);
                        kanjiIdList.append(newKanjiId);
                        qDebug()<<"new kanji"<< newKanjiId;
                    }
                }

                //first element of array is the user id
                //then kanjiids of kanjis to add follows
                QJsonArray outputArr;
                outputArr.append(QJsonArray::fromStringList(kanjiIdList));

                insertNewKanjiForUser(outputArr);
                //qDebug()<<"To InsertData"<< toInsertData;
            }
        }
        else{
            qDebug() << "Error: " << reply->errorString();
            reply->abort();
        }
    });


}

void ApiConnectionClass::insertNewKanjiForUser(QJsonArray arrayToInsert)
{
    //TODO api query to insert items
    QUrl dbInsertUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/kanji_resource/per_user/insert_kanji"); // Replace with your actual login endpoint
    QNetworkRequest request(dbInsertUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject insertData;
    insertData["KanjiIdList"] = arrayToInsert;
    insertData["UserId"] =  "USR-2";
    QJsonDocument userDoc(insertData);
    QByteArray dataToInsert = userDoc.toJson();
    //TODO fix body send array to body
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->put(request, dataToInsert);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            // Process the responseData (e.g., parse JSON)
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                rootObject = jsonDoc.object();
                qDebug()<<"insert return"<<rootObject.value("body").toString();
                //QString jsonText;
                reply->abort();
            }
            qDebug()<<"Insert Successful";
        }
        else{
            qDebug() << "Error: " << reply->errorString();
            reply->abort();
        }
    });
}
