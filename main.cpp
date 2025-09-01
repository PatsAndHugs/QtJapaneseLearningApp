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
    qmlRegisterType<KanjiListModel>("KanjiClass",1,0,"KanjiListModel");
    qmlRegisterUncreatableType<KanjiList>("KanjiClass", 1, 0, "KanjiList",
        QStringLiteral("KanjiList Should not be created in Qml"));

    KanjiList kanjiList;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty(QStringLiteral("kanjiList"), &kanjiList);
    engine.loadFromModule("QtJapaneseLearningApp", "Main");

    return app.exec();
}
