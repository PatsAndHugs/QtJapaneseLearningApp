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

    ColumnLayout{
        id:_learnKanjiCol
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter
        anchors.topMargin: parent.height * .10
        spacing: 10
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight:  Qt.platform.os === "android" ? parent.height * .25 : parent.height * .2
            Layout.preferredWidth: parent.width * .5
            color:"transparent"
            Label{
                id:_learnKanjiTxt
                anchors.centerIn: parent
                text:"月"//kanjiList.kanjiTxt
                font.pixelSize: parent.width * .20
                color:"white"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: parent.height * .2
            Layout.preferredWidth: parent.width * .5
            color:"transparent"
            Label{
                id:_learnEnglishMeaningTxt
                anchors.centerIn: parent
                text:kanjiList.englishNameTxt
                font.pixelSize: parent.width * .05
                color:"white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: parent.height * .2
            Layout.preferredWidth: parent.width * .5
            color:"transparent"
            Label{
                id:_learnKunyomiTxt
                anchors.centerIn: parent
                text:kanjiList.kunyomiTxt
                font.pixelSize: parent.width * .05
                color:"white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: parent.height * .2
            Layout.preferredWidth: parent.width * .5
            color:"transparent"
            Label{
                id:_learnOnyomiTxt
                anchors.centerIn: parent
                text:kanjiList.onyomiTxt
                font.pixelSize: parent.width * .05
                color:"white"
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
        AppButton{
            id:_drawBtn
            text:qsTr("DRAW")
            btnBgColor: _drawBtn.hovered ? "#ffff66" : "white"
            Layout.preferredHeight: Qt.platform.os === "android" ? parent.height * .2 : parent.height * .1
            Layout.preferredWidth: parent.width * .15
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
            Layout.preferredHeight: Qt.platform.os === "android" ? parent.height * .2 : parent.height * .1
            Layout.preferredWidth: parent.width * .15
            Layout.column: 4
            onClicked: {
                console.log("draw")
                _canvas.penColor = "gray"
                _canvas.penLineWidth = 50
            }
        }
        Rectangle{
            Layout.columnSpan: 5
            Layout.fillWidth: true
            Layout.fillHeight: true
            color:"gray"
            radius: 12
            Canvas {
                id: _canvas
                property real lastX
                property real lastY
                property color penColor
                property real penLineWidth
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
    }
}
