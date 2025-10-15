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
                    QString newString = lastKanjiId.remove("\"");
                    newString = newString.remove("KI-");
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
            }
        }
        else{
            qDebug() << "Error: " << reply->errorString();
            reply->abort();
        }
    });
}

void ApiConnectionClass::loginUser(QString usernameVal, QString passwordVal)
{
    QJsonObject userCredObj;
    userCredObj["username"] = usernameVal;
    userCredObj["password"] = encryptString(passwordVal);
    QJsonDocument userDoc(userCredObj);
    QByteArray userCredData = userDoc.toJson();
    //API
    QUrl checkUserUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/user_resource/current_user");
    QNetworkRequest request(checkUserUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager *loginManager = new QNetworkAccessManager(this);
    QNetworkReply *loginReply = loginManager->post(request, userCredData);

    qDebug()<<"usercreddata"<<userCredData;
    QObject::connect(loginReply, &QNetworkReply::finished, this, [=]() {
        if (loginReply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = loginReply->readAll();
            loginReply->deleteLater();
            loginManager->deleteLater();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                rootObject = jsonDoc.object();
                qDebug()<<"Root obj"<<rootObject.value("statusCode").toInt();
                if(rootObject.value("statusCode") == 200)
                {
                    qDebug() << "Login successful:";
                    m_loginResult = true;
                }
                else if(rootObject.value("statusCode") == 401)
                {
                    qDebug() << "Login Failed: Invalid Username or Password";
                    m_loginResult = false;
                }
                else
                {
                    qDebug() << "Login Failed " << loginReply->errorString();
                    m_loginResult = false;
                }

                QString newString = rootObject.value("body").toString();
                newString.remove("\"");
                m_userId = newString;
            }

        }
        else{
            qDebug() << "Login failed: " << loginReply->errorString();
            m_loginResult = false;
        }
        emit loginResultReceived();
        loginReply->deleteLater();
    });
}

void ApiConnectionClass::registerNewUser(QString usernameVal, QString passwordVal, QString emailVal)
{
    QString encryptedPassword = encryptString(passwordVal);

    QUrl dbInsertUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/user_resource/new_user");
    QNetworkRequest request(dbInsertUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject insertData;
    insertData["username"] = usernameVal;
    insertData["password"] = encryptedPassword;
    insertData["email"] = emailVal;
    QJsonDocument userDoc(insertData);
    QByteArray dataToInsert = userDoc.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //TODO Change to post
    QNetworkReply *reply = manager->post(request, dataToInsert);

    //check if username is not already taken
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                rootObject = jsonDoc.object();

                for (QJsonObject::iterator it = rootObject.begin(); it != rootObject.end(); ++it) {
                    //qDebug() << "Key:" << it.key() << "Value:" << it.value();
                    if(it.key() == "statusCode")
                    {
                        if(it.value() == 200)
                        {
                            qDebug() << "Username is Valid";
                            insertNewUser(insertData);
                        }
                        else if(it.value() == 401)
                        {
                            qDebug() << "Username is Already Taken";
                            m_registerResult = false;
                            emit registerFinished();
                        }
                        else
                        {
                            qDebug() << "Error";
                            m_registerResult = false;
                            emit registerFinished();
                        }
                    }
                }
            }
            reply->abort();
        }
        else{
            m_registerResult = false;
            emit registerFinished();
            qDebug() << "Error: " << reply->errorString();
            reply->abort();
        }
        reply->abort();
    });
}

void ApiConnectionClass::insertNewKanjiForUser(QJsonArray arrayToInsert)
{
    QUrl dbInsertUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/kanji_resource/per_user/insert_kanji"); // Replace with your actual login endpoint
    QNetworkRequest request(dbInsertUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject insertData;
    insertData["KanjiIdList"] = arrayToInsert;
    insertData["UserId"] =  "USR-2";
    QJsonDocument userDoc(insertData);
    QByteArray dataToInsert = userDoc.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //TODO Change to post
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
            reply->abort();
        }
        else{
            qDebug() << "Error: " << reply->errorString();
            reply->abort();
        }
    });
}

QString ApiConnectionClass::encryptString(QString stringVal)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(stringVal.toUtf8());
    QByteArray resultHash = hash.result();
    return resultHash.toHex();
}

void ApiConnectionClass::insertNewUser(QJsonObject userDataVal)
{
    QUrl dbInsertUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/user_resource/new_user"); // Replace with your actual login endpoint
    QNetworkRequest request(dbInsertUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument userDoc(userDataVal);
    QByteArray dataToInsert = userDoc.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->put(request, dataToInsert);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            m_registerResult = true;
            emit registerFinished();
            qDebug()<<"Insert Successful";
        }
        else{
            m_registerResult = false;
            emit registerFinished();
            qDebug() << "Error: " << reply->errorString();
        }
        reply->abort();
    });
}

