#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <dbconnectionclass.h>
#include <kanjilistmodel.h>
#include <kanjilist.h>
#include <kanjiquiz.h>
#include <kanjiquizresultmodel.h>
#include <userloginclass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<DbConnectionClass>("JapaneseLearningApp.DbConnectionClass",1,0,"DbConnClass");
    qmlRegisterType<KanjiListModel>("KanjiClass",1,0,"KanjiListModel");
    qmlRegisterType<KanjiQuizResultModel>("KanjiClass",1,0,"KanjiQuizResultModel");
    qmlRegisterUncreatableType<KanjiList>("KanjiClass", 1, 0, "KanjiList",
        QStringLiteral("KanjiList Should not be created in Qml"));


    qmlRegisterType<KanjiQuiz>("KanjiClass",1,0,"KanjiQuiz");

    DbConnectionClass connClass;
    connClass.setupConn();

    KanjiList kanjiList;
    KanjiQuiz kanjiQuiz;
    UserLoginClass loginClass;


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty(QStringLiteral("kanjiList"), &kanjiList);
    engine.rootContext()->setContextProperty(QStringLiteral("kanjiQuiz"), &kanjiQuiz);
    engine.rootContext()->setContextProperty(QStringLiteral("userLogin"), &loginClass);


    engine.loadFromModule("QtJapaneseLearningApp", "Main");

    return app.exec();
}
