#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <dbconnectionclass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<DbConnectionClass>("JapaneseLearningApp.DbConnectionClass",1,0,"DbConnClass");
    DbConnectionClass* dbConnClass = new DbConnectionClass;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("KanjiModel", dbConnClass->getModel());
    engine.loadFromModule("QtJapaneseLearningApp", "Main");

    return app.exec();
}
