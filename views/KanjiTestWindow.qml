import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_testAppWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Kanji Test")
    color:"#023D54"

    property bool kanjiTestSwitchState: false

    header: MenuBar{
        MenuBarItem{
            text: qsTr("Menu")
            menu:Menu {
                id:_menu
                MenuItem{
                    text:qsTr("Back To Main Menu")
                    onClicked:{
                        _kanjiMainWindow.show()
                        _testAppWindow.close()
                    }
                }

                MenuItem{text:qsTr("Cancel")}
            }
        }
    }
    GridLayout{
        id:_mainGrid
        //anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        //anchors.bottom: _canvasGrid.top
        anchors.topMargin: 100
        anchors.rightMargin: 20
        columns: 2
        rowSpacing: 20

        Rectangle{
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            AppButton{
                id:_kanjiShowBtn
                anchors.centerIn: parent
                text: qsTr("Show Kanji")
                onClicked:{
                    _lblKanji.visible = true
                    _kanjiShowBtn.visible = false
                }
            }
            Label{
                id:_lblKanji
                color: "black"
                font.pointSize: 100
                horizontalAlignment: Text.AlignHCenter
                text:kanjiQuiz.kanjiTxt
                anchors.centerIn: parent
                visible: false
            }


        }

        Label{
            id:_lblEnglishMeaning
            color: "black"
            font.pointSize: 50
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            text:kanjiQuiz.englishNameTxt
            Layout.columnSpan: 2
            Layout.row: 2
            Layout.topMargin: 30
        }

        TextField{
            id:_txtFieldKunyomi
            placeholderText: qsTr("Kunyomi...")
            font.pointSize: 20
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.columnSpan: 2
            Layout.row: 3
            Layout.topMargin: 30
        }

        TextField{
            id:_txtFieldOnyomi
            placeholderText: qsTr("Onyomi...")
            font.pointSize: 20
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.columnSpan: 2
            Layout.row: 4
        }

        AppButton{
            id: _confirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _confirmBtn.hovered ? "#ffff66" : "white"
            font.pointSize: 15
            Layout.row: 5
            Layout.leftMargin: 10
            onClicked: {
                kanjiQuiz.kunyomiTxt = _txtFieldKunyomi.text
                kanjiQuiz.onyomiTxt = _txtFieldOnyomi.text
                _kanjiShowBtn.visible = true
                _lblKanji.visible = false
                kanjiQuiz.getNextItem()
            }

        }
        AppButton{
            id: _skipBtn
            text: qsTr("Skip")
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _skipBtn.hovered ? "#ffff66" : "white"
            font.pointSize: 15
            Layout.rightMargin: 10

            onClicked:{
                if(kanjiTestSwitchState === true)
                {
                    kanjiQuiz.kunyomiTxt = _txtFieldKunyomi.text
                    kanjiQuiz.onyomiTxt = _txtFieldOnyomi.text
                    kanjiQuiz.skipItem()
                    _kanjiShowBtn.visible = true
                    _lblKanji.visible = false
                }
                else
                    _kanjiTestConfirmMsgDialog.open()
            }
        }

        AppSwitchCtrl{
            id:_KanjiTestMsgDiagSwitch
            switchText: "Disable Message Button on Skip"
            switchChecked: false
            Layout.column:1
            Layout.alignment: Qt.AlignHCenter //| Qt.AlignVCenter
            Layout.rightMargin: 100
            Layout.row: 6
            onToggle:{
                kanjiTestSwitchState = !kanjiTestSwitchState
                console.log("kappa")
            }

        }
    }

    GridLayout{
        id: _canvasGrid
        //anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.top: _mainGrid.bottom
        anchors.topMargin: 50
        anchors.bottom:parent.bottom
        anchors.left: parent.left
        anchors.rightMargin: 10
        columns:5
        AppButton{
            id:_drawBtn
            text:qsTr("DRAW")
            btnBgColor: _drawBtn.hovered ? "#ffff66" : "white"
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100
            Layout.column: 3
            onClicked: {
                console.log("draw")
                _canvas.penColor = "black"
                _canvas.penLineWidth = 3
            }
        }
        AppButton{
            id:_eraseBtn
            text:qsTr("ERASE")
            btnBgColor: _eraseBtn.hovered ? "#ffff66" : "white"
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100
            Layout.column: 4
            onClicked: {
                console.log("draw")
                _canvas.penColor = "#023D54"
                _canvas.penLineWidth = 30
            }
        }

        Canvas {
            id: _canvas
            property real lastX
            property real lastY
            property color penColor
            property real penLineWidth
            Layout.columnSpan: 5
            Layout.fillWidth: true
            Layout.fillHeight: true
            onPaint: {
                var ctx = getContext('2d')
                ctx.lineWidth = penLineWidth
                ctx.strokeStyle = penColor
                ctx.beginPath()
                ctx.moveTo(lastX, lastY)
                lastX = area.mouseX
                lastY = area.mouseY
                ctx.lineTo(lastX, lastY)
                ctx.stroke()
            }

            MouseArea {
                id: area
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onPressed:{
                    _canvas.lastX = mouseX
                    _canvas.lastY = mouseY
                }
                onPositionChanged: (mouse) => {
                    _canvas.requestPaint()
                }
                onClicked: console.log("canvas clicked")
            }

        }
    }

    AppMsgDialog
    {
        id: _kanjiTestConfirmMsgDialog
        anchors.centerIn: parent
        message:"Skip Item?"
        acceptButtonText: "Confirm"
        cancelButtonText: "Cancel"

        onAccepted:{
            kanjiQuiz.kunyomiTxt = _txtFieldKunyomi.text
            kanjiQuiz.onyomiTxt = _txtFieldOnyomi.text
            kanjiQuiz.skipItem()
            _kanjiShowBtn.visible = true
            _lblKanji.visible = false
        }
    }

    Connections{
        target: kanjiQuiz
        function onGetNextItemTriggered(){
            _txtFieldKunyomi.text = "";
            _txtFieldOnyomi.text = "";
        }
        function onQuizFinished(){
            console.log("skipped finished")
            var component = Qt.createComponent("KanjiTallyWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_kanjiMainWindow);
                if(newWindow){
                    _testAppWindow.close()
                    newWindow.show()
                }
            }
            else {
                console.log("Error loading component:", component.errorString());
            }
        }
    }
}
