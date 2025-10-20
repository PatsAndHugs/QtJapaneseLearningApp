#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include <dbconnectionclass.h>
#include <kanjilistmodel.h>
#include <kanjilist.h>
#include <kanjiquiz.h>
#include <kanjiquizresultmodel.h>
#include <userloginclass.h>
#include <filterkanjilistmodel.h>
#include <vocab/vocablist.h>
#include <vocab/vocablistmodel.h>
#include <vocab/filtervocablistmodel.h>
#include <vocab/vocabquiz.h>
#include <vocab/vocabquizresultmodel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("MyCompnay");
    app.setApplicationName("JapaneseLearningApp");

    qmlRegisterType<DbConnectionClass>("JapaneseLearningApp.DbConnectionClass",1,0,"DbConnClass");
    qmlRegisterType<KanjiListModel>("KanjiClass",1,0,"KanjiListModel");
    qmlRegisterType<FilterKanjiListModel>("KanjiClass",1,0,"FilterKanjiListModel");
    qmlRegisterType<KanjiQuizResultModel>("KanjiClass",1,0,"KanjiQuizResultModel");
    // qmlRegisterUncreatableType<KanjiList>("KanjiClass", 1, 0, "KanjiList",
    //     QStringLiteral("KanjiList Should not be created in Qml"));

    qmlRegisterType<FilterVocabListModel>("VocabClass",1,0,"FilterVocabListModel");
    qmlRegisterType<VocabQuizResultModel>("VocabClass",1,0,"VocabQuizResultModel");
    qmlRegisterType<VocabListModel>("VocabClass",1,0,"VocabListModel");
    qmlRegisterUncreatableType<VocabList>("VocabClass", 1, 0, "VocabList",
        QStringLiteral("VocabList Should not be created in Qml"));


    qmlRegisterType<KanjiQuiz>("KanjiClass",1,0,"KanjiQuiz");
    qmlRegisterType<VocabQuiz>("VocabClass",1,0,"VocabQuiz");

    DbConnectionClass connClass;
    //connClass.setupConn();

    KanjiList kanjiList;
    KanjiQuiz kanjiQuiz;
    UserLoginClass loginClass;
    VocabList vocabList;
    VocabQuiz vocabQuiz;


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
    engine.rootContext()->setContextProperty(QStringLiteral("dbConn"), &connClass);
    engine.rootContext()->setContextProperty(QStringLiteral("vocabList"), &vocabList);
    engine.rootContext()->setContextProperty(QStringLiteral("vocabQuiz"), &vocabQuiz);


    // QSettings settings;
    // QString windowToOpen;
    // if(settings.value("loginstate").toBool() == true)
    //     windowToOpen = "Main";
    // else
    //     windowToOpen = "LoginWindow";

    // engine.loadFromModule("QtJapaneseLearningApp", windowToOpen);
    engine.loadFromModule("QtJapaneseLearningApp", "Main");


    return app.exec();
}
