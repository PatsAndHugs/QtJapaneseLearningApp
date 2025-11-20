import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_learnKanjiWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Study Kanji Window")
    color:"#023D54"

    Component.onCompleted: {
        if (Qt.platform.os === "android") {
            _learnKanjiWindow.width = Screen.width
            _learnKanjiWindow.height = Screen.height
        }
    }


    GridLayout{
        id:_learnKanjiGrid
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter
        anchors.topMargin: Qt.platform.os === "android" ? parent.height * .07 : parent.height * .05
        anchors.rightMargin: parent.width * .01
        columns:3
        ColumnLayout{
            Layout.fillWidth: true
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 1
            Layout.alignment: Qt.AlignTop
            Rectangle {
                id:_kanjiTxtRect
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                Layout.leftMargin: 5
                color:"lightgreen"
                radius: 5
                Label{
                    id:_learnKanjiTxt
                    anchors.centerIn: parent
                    text:kanjiList.kanjiTxt
                    font.pixelSize: parent.width * .30
                    color:"#023D54"
                }
            }

            Rectangle {
                id: _jlptLevelRect
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                Layout.leftMargin: 5
                color:"yellow"
                radius: 5
                Label{
                    id:_jlptLevelLbl
                    anchors.centerIn: parent
                    text:kanjiList.jlptLevelTxt
                    font.pixelSize: parent.width * .10
                    color:"#023D54"
                }
            }
        }

        Rectangle{
            id:_cardbase
            color: "white"
            radius: 8
            Layout.preferredHeight: _kanjiTxtRect.height + _jlptLevelRect.height
            Layout.preferredWidth: _learnKanjiWindow.width * .75
            Layout.row: 0
            Layout.column: 1
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignTop
            ColumnLayout{
                id:_colLayout
                anchors.fill: parent
                anchors.margins: parent.height *.05
                Text{
                    id:_englishMeaningTxt
                    color: "#023D54"
                    font.pixelSize: 30
                    fontSizeMode: Text.Fit
                    text:kanjiList.englishNameTxt
                }

                Text{
                    id:_kunyomiTxt
                    Layout.leftMargin: _colLayout.width * .05
                    color: "#023D54"
                    font.pixelSize: 20
                    fontSizeMode: Text.Fit
                    Layout.fillWidth: true
                    wrapMode: Text.Wrap
                    text:kanjiList.kunyomiTxt
                }

                Text{
                    id:_onyomiTxt
                    Layout.leftMargin: _colLayout.width * .05
                    color: "#023D54"
                    font.pixelSize: 20
                    fontSizeMode: Text.Fit
                    Layout.fillWidth: true
                    wrapMode: Text.Wrap
                    text:kanjiList.onyomiTxt
                }
            }
        }
    }

    GridLayout{
        id: _canvasGrid
        anchors.right: parent.right
        anchors.top: parent.verticalCenter
        anchors.bottom:parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 50
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        columns:5

        Rectangle{
            Layout.columnSpan: 5
            Layout.fillWidth: true
            Layout.fillHeight: true
            color:"gray"
            radius: 12
            z: 0
            Canvas {
                id: _canvas
                property real lastX
                property real lastY
                property color penColor
                property real penLineWidth: 3
                anchors.fill: parent
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

        AppButton{
            id:_drawBtn
            Layout.alignment: Qt.AlignTop
            text:qsTr("DRAW")
            btnBgColor: "#ffff66"
            Layout.preferredHeight: Qt.platform.os === "android" ? parent.height * .2 : parent.height * .1
            Layout.preferredWidth: parent.width * .15
            Layout.column: 3
            z:1
            onClicked: {
                console.log("draw")
                _drawBtn.btnBgColor = "#ffff66"
                _eraseBtn.btnBgColor = "white"
                _canvas.penColor = "black"
                _canvas.penLineWidth = 3
            }
        }
        AppButton{
            id:_eraseBtn
            Layout.alignment: Qt.AlignTop
            text:qsTr("ERASE")
            btnBgColor: "white"
            Layout.preferredHeight: Qt.platform.os === "android" ? parent.height * .2 : parent.height * .1
            Layout.preferredWidth: parent.width * .15
            Layout.column: 4
            z:1
            onClicked: {
                console.log("erase")
                _drawBtn.btnBgColor = "white"
                _eraseBtn.btnBgColor = "#ffff66"
                _canvas.penColor = "gray"
                _canvas.penLineWidth = 50
            }
        }
    }

    AppButton{
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        font.pixelSize: parent.width * .03
        text:qsTr("back to Main")
        width: Qt.platform.os === "android" ? parent.width * .2 : parent.width * .15
        height: parent.height * .04
        textBottomPadding: Qt.platform.os === "android" ? height * .5 : height * .2
        onClicked:{
            kanjiList.clearAllSelectedItems()
            _learnKanjiWindow.close()
            _learnMainWindow.show()
        }
    }

}
