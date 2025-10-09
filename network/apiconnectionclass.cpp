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
                            reply->deleteLater();
                        }
                    }
                }
            }
        }
        else{
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
}
