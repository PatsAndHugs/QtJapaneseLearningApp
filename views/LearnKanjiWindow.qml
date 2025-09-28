import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

//import KanjiClass 1.0

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
    AppButton{
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        text:qsTr("back to Main")
        width: 150
        height: 50
        onClicked:{
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
        anchors.topMargin: 100
        spacing: 10
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color:"transparent"
            Label{
                id:_learnKanjiTxt
                anchors.centerIn: parent
                text:kanjiList.kanjiTxt
                font.pointSize: 100
                color:"white"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color:"transparent"
            Label{
                id:_learnEnglishMeaningTxt
                anchors.centerIn: parent
                text:kanjiList.englishNameTxt
                font.pointSize: 30
                color:"white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color:"transparent"
            Label{
                id:_learnKunyomiTxt
                anchors.centerIn: parent
                text:kanjiList.kunyomiTxt
                font.pointSize: 30
                color:"white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            color:"transparent"
            Label{
                id:_learnOnyomiTxt
                anchors.centerIn: parent
                text:kanjiList.onyomiTxt
                font.pointSize: 30
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
