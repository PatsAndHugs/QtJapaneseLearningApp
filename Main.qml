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

            axisX: BarCategoryAxis {
                id:_barCategoryAxis
                categories: userLogin.barCategory//["2023", "2024", "2025"]
                lineVisible: false
            }
            axisY: ValueAxis {
                min: 0
                max: 20
                subTickCount: 4
            }
            BarSeries {
                id: _barSeries
                BarSet {
                    color:"yellow"
                    values: userLogin.barValues
                }

                BarModelMapper{

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
            id:_kanjiLearnBtn
            text: "Learn Kanji"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: {
                _loadingSpinner.running = !_loadingSpinner.running
                _kanjiLearnBtn.enabled = false
                kanjiList.addItemsForLearning()
            }
        }

        AppButton{
            id:_vocabLearnBtn
            text: "Learn Vocab"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: {
                _loadingSpinner.running = !_loadingSpinner.running
                _vocabLearnBtn.enabled = false
                vocabList.addItemsForLearning()
            }
        }

        AppButton{
            id:_kanjiTestBtn
            text: "Kanji Test"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: {
                _loadingSpinner.running = !_loadingSpinner.running
                _kanjiTestBtn.enabled = false
                kanjiList.addItems()
            }
        }

        AppButton{
            id:_vocabTestBtn
            text: "Vocab Test"
            Layout.preferredHeight: parent.height / 10
            Layout.fillWidth: true
            onClicked: {
                _loadingSpinner.running = !_loadingSpinner.running
                _vocabTestBtn.enabled = false
                vocabList.addItems()
            }
        }
    }

    BusyIndicator{
        id: _loadingSpinner
        anchors.centerIn: parent
        running: false
        width: parent.width * .20
        height: parent.width * .20
        palette.dark: "lightgreen"
    }

    Connections{
        target: kanjiList
        function onFetchedKanjiListFromApiForLearning(){
            var component = Qt.createComponent("views/LearnMainWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_mainAppWindow);
                if(newWindow){
                    console.log("clicked")
                    _mainAppWindow.hide()
                    newWindow.show()
                    _loadingSpinner.running = !_loadingSpinner.running
                    _kanjiLearnBtn.enabled = true
                }
            }
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
                    _loadingSpinner.running = !_loadingSpinner.running
                    _kanjiTestBtn.enabled = true
                }
            }
        }
    }

    Connections{
        target: vocabList
        function onFetchedVocabListFromApiForLearning(){
            var component = Qt.createComponent("views/LearnVocabMainWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_mainAppWindow);
                if(newWindow){
                    console.log("clicked")
                    _mainAppWindow.hide()
                    newWindow.show()
                    _loadingSpinner.running = !_loadingSpinner.running
                    _vocabLearnBtn.enabled = true
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
                    _loadingSpinner.running = !_loadingSpinner.running
                    _vocabTestBtn.enabled = true
                }
            }
        }
    }

}

