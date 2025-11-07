cmake_minimum_required(VERSION 3.16)

project(QtJapaneseLearningApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Xml Sql Network Graphs)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQtJapaneseLearningApp
    main.cpp
)

qt_add_qml_module(appQtJapaneseLearningApp
    URI QtJapaneseLearningApp
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES
        QML_FILES DbConnWindow.qml
        SOURCES xmlreaderclass.h xmlreaderclass.cpp
        RESOURCES AppResources.qrc
        SOURCES dbconnectionclass.h dbconnectionclass.cpp
        QML_FILES
        QML_FILES
        SOURCES kanjilistmodel.h kanjilistmodel.cpp
        SOURCES kanjilist.h kanjilist.cpp
        QML_FILES
        QML_FILES
        QML_FILES
        QML_FILES views/KanjiTestWindow.qml
        SOURCES kanjiquiz.h kanjiquiz.cpp
        QML_FILES
        QML_FILES views/KanjiTallyWindow.qml
        SOURCES kanjiquizresultmodel.h kanjiquizresultmodel.cpp
        QML_FILES views/KanjiListCard.qml
        QML_FILES views/LogInPopUp.qml
        SOURCES userloginclass.h userloginclass.cpp
        QML_FILES views/RegisterPopUp.qml
        SOURCES filterkanjilistmodel.h filterkanjilistmodel.cpp
        QML_FILES
        QML_FILES views/AppButton.qml
        QML_FILES views/AppMsgDialog.qml
        QML_FILES views/AppSwitchCtrl.qml
        QML_FILES views/KanjiMainWindow.qml
        QML_FILES views/VocabMainWindow.qml
        SOURCES vocab/vocablist.h vocab/vocablist.cpp
        SOURCES vocab/vocablistmodel.h vocab/vocablistmodel.cpp
        SOURCES vocab/filtervocablistmodel.h vocab/filtervocablistmodel.cpp
        SOURCES vocab/vocabquiz.h vocab/vocabquiz.cpp
        QML_FILES views/VocabTestWindow.qml
        QML_FILES views/VocabTallyWindow.qml
        SOURCES vocab/vocabquizresultmodel.h vocab/vocabquizresultmodel.cpp
        QML_FILES views/LearnMainWindow.qml
        QML_FILES views/LearnKanjiWindow.qml
        QML_FILES views/DbConnectionWindow.qml
        SOURCES network/apiconnectionclass.h network/apiconnectionclass.cpp
        SOURCES
        SOURCES
        QML_FILES views/LoginWindow.qml
        QML_FILES views/RegisterWindow.qml
        QML_FILES views/SearchTextField.qml
        SOURCES
        QML_FILES views/LearnVocabMainWindow.qml
        QML_FILES views/LearnVocabWindow.qml
)

# add resource items here
qt_add_resources(appQtJapaneseLearningApp "images"
    PREFIX "/image"
    FILES resources/silencesuzuka.png resources/Ryza_and_the_holy_tower_of_Pynnor.png
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtJapaneseLearningApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtJapaneseLearningApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtJapaneseLearningApp
    PRIVATE Qt6::Quick Qt6::Xml Qt6::Sql Qt6::Network Qt6::Graphs
)

include(GNUInstallDirs)
install(TARGETS appQtJapaneseLearningApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (ANDROID)
    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
endif()

if (ANDROID)
    add_android_openssl_libraries(appQtJapaneseLearningApp)
endif()

