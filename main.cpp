#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <dbconnectionclass.h>
#include <kanjilistmodel.h>
#include <kanjilist.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<DbConnectionClass>("JapaneseLearningApp.DbConnectionClass",1,0,"DbConnClass");
    qmlRegisterType<KanjiListModel>("KanjiListModel",1,0,"KanjiListModel");
    DbConnectionClass* dbConnClass = new DbConnectionClass;
    KanjiList kanjiList;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("KanjiModel", dbConnClass->getModel());
    //engine.rootContext()->setContextProperty(QStringLiteral("kanjiList"), &kanjiList);
    engine.loadFromModule("QtJapaneseLearningApp", "Main");

    return app.exec();
}
