import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import VocabClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_learnVocabWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Study Vocab Window")
    color:"#023D54"

    Component.onCompleted: {
        if (Qt.platform.os === "android") {
            _learnVocabWindow.width = Screen.width
            _learnVocabWindow.height = Screen.height
        }
    }

    GridLayout{
        id:_learnVocabGrid
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
            Rectangle{
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                Layout.leftMargin: 5
                color:"lightgreen"
                radius: 5
                Label{
                    id:_learnVocabTxt
                    anchors.centerIn: parent
                    text:vocabList.kanjiText
                    font.pixelSize: parent.width * .30
                    color:"#023D54"
                }
            }
            Rectangle{
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                Layout.leftMargin: 5
                color:"yellow"
                radius: 5
                Label{
                    id:_learnVocabLevel
                    anchors.centerIn: parent
                    text:vocabList.jlptLevel
                    font.pixelSize: parent.width * .10
                    color:"#023D54"
                }
            }
        }

        ListView{
            id:_itemList
            Layout.preferredHeight: _learnVocabGrid.height
            Layout.preferredWidth: _learnVocabWindow.width * .75
            Layout.row: 0
            Layout.column: 1
            Layout.columnSpan: 2
            spacing: 10
            model: VocabDetaisModel{
                list: vocabList.getVocabDetailsList()
            }

            delegate: LearnVocabListCard{ id:_wrapper
                                    wordType: model.wordType
                                    englishMeaning: model.vocabMeaning
                                    lblTextColor: "#023D54"
                                    width: _itemList.width
                                    height: Qt.platform.os === "android" ? _itemList.height * 0.20 : _itemList.height * 0.12
                                    color: "white"
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
            vocabList.clearAllSelectedItems()
            _learnVocabWindow.close()
            _learnVocabMainWindow.show()
        }
    }
}
