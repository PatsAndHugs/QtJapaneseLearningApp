import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_mainAppWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Kanji Test")
    color:"#023D54"

    GridLayout{
        id:_mainGrid
        //anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        //anchors.bottom: _canvasGrid.top
        anchors.topMargin: 200
        columns: 2
        rowSpacing: 20

        Label{
            id:_lblKanji
            color: "black"
            font.pointSize: 50
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignCenter
            text:kanjiQuiz.kanjiTxt
            Layout.columnSpan: 2
        }

        Label{
            id:_lblEnglishMeaning
            color: "black"
            font.pointSize: 30
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            text:kanjiQuiz.englishNameTxt
            Layout.columnSpan: 2
            Layout.row: 2
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

        Button{
            id: _confirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            //color: _confirmBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            Layout.row: 5
            Layout.leftMargin: 10
            onClicked: {
                kanjiQuiz.kunyomiTxt = _txtFieldKunyomi.text
                kanjiQuiz.onyomiTxt = _txtFieldOnyomi.text
                if(kanjiQuiz.getNextItem()){
                    _txtFieldKunyomi.text = "";
                    _txtFieldOnyomi.text = "";
                }

            }
        }
        Button{
            id: _skipBtn
            text: qsTr("Skip")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            //color: _confirmBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            Layout.rightMargin: 10
            onClicked:{
                kanjiQuiz.kunyomiTxt = _txtFieldKunyomi.text
                kanjiQuiz.onyomiTxt = _txtFieldOnyomi.text
                kanjiQuiz.testFunc()
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
        columns:5
        Button{
            id:_drawBtn
            text:qsTr("DRAW")
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100
            Layout.column: 3
            onClicked: {
                console.log("draw")
                _canvas.penColor = "black"
                _canvas.penLineWidth = 3
            }
        }
        Button{
            id:_eraseBtn
            text:qsTr("ERASE")
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
}
