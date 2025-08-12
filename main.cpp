#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <dbconnectionclass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<DbConnectionClass>("JapaneseLearningApp.DbConnectionClass",1,0,"DbConnClass");


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QtJapaneseLearningApp", "Main");

    return app.exec();
}
