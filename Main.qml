import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Effects
import Qt.labs.settings 1.0
import QtCore
import QtGraphs

//import JapaneseLearningApp.DbConnectionClass
//import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_mainAppWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Japanese Learning App")
    color:"#023D54"

    header: MenuBar{
        MenuBarItem{
            text: qsTr("Menu")
            menu:Menu{
                MenuItem{
                    id:_userMenuItem
                    text: qsTr("Logout")
                    onClicked:{
                        userLogin.logout()
                        var component = Qt.createComponent("views/LoginWindow.qml")
                        if(component.status === Component.Ready){
                            var newWindow = component.createObject(_mainAppWindow);
                            if(newWindow){
                                newWindow.show()
                                _mainAppWindow.hide()
                            }
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        if(userLogin.getSavedLoginState() !== true){
            var component = Qt.createComponent("views/LoginWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_mainAppWindow);
                if(newWindow){
                    newWindow.show()
                    _mainAppWindow.hide()
                }
            }
        }

        if (Qt.platform.os === "android") {
            _mainAppWindow.width = Screen.width
            _mainAppWindow.height = Screen.height
        }
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        // Image{
        //     id: _mainImg
        //     source: "qrc:/image/resources/Ryza_and_the_holy_tower_of_Pynnor.png"
        //     fillMode: Image.PreserveAspectCrop // Adjust as needed
        //     Layout.preferredHeight: parent.height / 2
        //     Layout.fillWidth: true
        // }

        GraphsView {
            Layout.preferredHeight: parent.height / 2
            Layout.fillWidth: true

            theme: GraphsTheme {
                readonly property color c1: "white"
                readonly property color c2: "transparent"
                //colorScheme: GraphsTheme.ColorScheme.Light
                theme: GraphsTheme.Theme.UserDefined
                colorStyle: "Uniform"
                backgroundColor: "lightblue"
                backgroundVisible: false
                seriesColors: ["#2CDE85", "#DBEB00"]
                axisX.mainColor: c2
                axisY.mainColor: c2
                axisX.subColor: c2
                axisY.subColor: c2
                axisX.labelTextColor: c1
                axisY.labelTextColor: c1
                gridVisible: false

            }
            axisX: ValueAxis {
                max: 5
                tickInterval: 1
                subTickCount: 9
                labelDecimals: 1
            }
            axisY: ValueAxis {
                max: 10
                tickInterval: 1
                subTickCount: 4
                labelDecimals: 1
            }

            component Marker : Rectangle {
                width: 16
                height: 16
                color: "#ffffff"
                radius: width * 0.5
                border.width: 4
                border.color: "#000000"
            }

            LineSeries{
                id: lineSeries
                width: 4
                pointDelegate: Marker{}
            }

            Component.onCompleted:{
                for(var i = 0; i < userLogin.lineSeries.count;i++){
                    lineSeries.append(userLogin.lineSeries.at(i).x, userLogin.lineSeries.at(i).y)
                }
            }
        }

        RowLayout{
            id:_mainUserStatsRow
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 15
            //spacing:10

            Rectangle {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredHeight: parent.height
                //Layout.preferredWidth: parent.width / 3
                color: "white"
                radius: 8
                Label{
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: userLogin.getSavedUsername()
                    color:"#023D54"
                    font.pixelSize: parent.width / 10
                    font.bold: true
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredHeight: parent.height
                //Layout.preferredWidth: parent.width / 3
                color: "white"
                radius: 8

                Label{
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    text: qsTr("Kanji: 5")
                    color:"#023D54"
                    font.pixelSize: parent.width / 10
                    font.bold: true
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredHeight: parent.height
                //Layout.preferredWidth: parent.width / 3
                color: "white"
                radius: 8

                Label{
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    text: qsTr("Vocab: 2")
                    color:"#023D54"
                    font.pixelSize: parent.width / 10
                    font.bold: true
                }
            }
        }

        AppButton{
            text: "Learn"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked:{
                var component = Qt.createComponent("views/LearnMainWindow.qml")
                if(component.status === Component.Ready){
                    var newWindow = component.createObject(_mainAppWindow);
                    if(newWindow){
                        console.log("clicked")
                        _mainAppWindow.hide()
                        newWindow.show()
                    }
                }
            }

        }

        AppButton{
            text: "Kanji Test"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: kanjiList.addItems()
        }

        AppButton{
            text: "Vocab Test"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: vocabList.addItems()
        }
    }

    Connections{
        target: kanjiList
        function onFetchedKanjiListFromApi(){
            var component = Qt.createComponent("views/KanjiMainWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_mainAppWindow);
                if(newWindow){
                    console.log("clicked")
                    _mainAppWindow.hide()
                    newWindow.show()
                }
            }
        }
    }

    Connections{
        target: vocabList
        function onFetchedVocabListFromApi(){
            var component = Qt.createComponent("views/VocabMainWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_mainAppWindow);
                if(newWindow){
                    console.log("clicked")
                    _mainAppWindow.hide()
                    newWindow.show()
                }
            }
        }
    }

}

