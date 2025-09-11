cmake_minimum_required(VERSION 3.16)

project(QtJapaneseLearningApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Xml Sql Network)

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
        QML_FILES ListItemCard.qml
        QML_FILES AppBaseBtn.qml
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
)

# add resource items here
qt_add_resources(appQtJapaneseLearningApp "images"
    PREFIX "/image"
    FILES resources/silencesuzuka.png
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
    PRIVATE Qt6::Quick Qt6::Xml Qt6::Sql Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appQtJapaneseLearningApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
