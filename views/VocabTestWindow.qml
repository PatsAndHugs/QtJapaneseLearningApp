import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import VocabClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_vocabTestAppWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Vocabulary Test")
    color:"#023D54"

    property bool vocabTestSwitchState: false

    header: MenuBar{
        MenuBarItem{
            text: qsTr("Menu")
            menu:Menu {
                id:_menu
                MenuItem{
                    text:qsTr("Back To Main Menu")
                    onClicked:{
                        _vocabMainWindow.show()
                        _vocabTestAppWindow.close()
                    }
                }

                MenuItem{text:qsTr("Cancel")}
            }
        }
    }
    GridLayout{
        id:_mainGrid
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.rightMargin: 20
        columns: 2
        rowSpacing: 20

        Label{
            id:_lblVocabKanji
            color: "black"
            font.pointSize: 100
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignCenter
            text:vocabQuiz.vocabKanjiTxt
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label{
            id:_lblEnglishMeaning
            color: "black"
            font.pointSize: 20
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            text:vocabQuiz.vocabMeaningTxt
            Layout.columnSpan: 2
            Layout.row: 2
            Layout.topMargin: 30
        }

        TextField{
            id:_txtFieldVocabReading
            placeholderText: qsTr("Vocab Reading...")
            font.pointSize: 20
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.columnSpan: 2
            Layout.row: 3
            Layout.topMargin: 30
        }

        AppButton{
            id: _vocabConfirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _vocabConfirmBtn.hovered ? "#ffff66" : "white"
            font.pointSize: 15
            Layout.row: 5
            Layout.leftMargin: 10
            property string getItemResult
            onClicked: {
                vocabQuiz.vocabReadingTxt = _txtFieldVocabReading.text
                getItemResult = vocabQuiz.getNextItem()

                if(getItemResult === "get"){
                    _txtFieldVocabReading.text = "";
                }
                else if(getItemResult === "finish"){
                    var component = Qt.createComponent("VocabTallyWindow.qml")
                    if(component.status === Component.Ready){
                        var newWindow = component.createObject(_vocabMainWindow);
                        if(newWindow){
                             _vocabTestAppWindow.close()
                            newWindow.show()
                        }
                    }
                    else {
                        console.log("Error loading component:", component.errorString());
                    }
                }

            }
        }
        AppButton{
            id: _vocabSkipBtn
            text: qsTr("Skip")
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _vocabSkipBtn.hovered ? "#ffff66" : "white"
            font.pointSize: 15
            Layout.rightMargin: 10

            onClicked:{
                if(vocabTestSwitchState === true)
                    skipFunc()
                else
                    _vocabTestConfirmMsgDialog.open()
            }
        }

        AppSwitchCtrl{
            id:_vocabTestMsgDiagSwitch
            switchText: "Disable Message Button on Skip"
            switchChecked: false
            Layout.column:1
            Layout.alignment: Qt.AlignHCenter //| Qt.AlignVCenter
            Layout.rightMargin: 100
            Layout.row: 6
            onToggle:{
                vocabTestSwitchState = !vocabTestSwitchState
                console.log("kappa")
            }
        }
    }

    // GridLayout{
    //     id: _vocabCanvasGrid
    //     //anchors.verticalCenter: parent.verticalCenter
    //     anchors.right: parent.right
    //     anchors.top: _mainGrid.bottom
    //     anchors.topMargin: 50
    //     anchors.bottom:parent.bottom
    //     anchors.left: parent.left
    //     anchors.rightMargin: 10
    //     columns:5
    //     AppButton{
    //         id:_vocabDrawBtn
    //         text:qsTr("DRAW")
    //         btnBgColor: _vocabDrawBtn.hovered ? "#ffff66" : "white"
    //         Layout.preferredHeight: 50
    //         Layout.preferredWidth: 100
    //         Layout.column: 3
    //         onClicked: {
    //             console.log("draw")
    //             _vocabCanvas.penColor = "black"
    //             _vocabCanvas.penLineWidth = 3
    //         }
    //     }
    //     AppButton{
    //         id:_vocabEraseBtn
    //         text:qsTr("ERASE")
    //         btnBgColor: _vocabEraseBtn.hovered ? "#ffff66" : "white"
    //         Layout.preferredHeight: 50
    //         Layout.preferredWidth: 100
    //         Layout.column: 4
    //         onClicked: {
    //             console.log("draw")
    //             _vocabCanvas.penColor = "#023D54"
    //             _vocabCanvas.penLineWidth = 30
    //         }
    //     }

    //     Canvas {
    //         id: _vocabCanvas
    //         property real lastX
    //         property real lastY
    //         property color penColor
    //         property real penLineWidth
    //         Layout.columnSpan: 5
    //         Layout.fillWidth: true
    //         Layout.fillHeight: true
    //         onPaint: {
    //             var ctx = getContext('2d')
    //             ctx.lineWidth = penLineWidth
    //             ctx.strokeStyle = penColor
    //             ctx.beginPath()
    //             ctx.moveTo(lastX, lastY)
    //             lastX = area.mouseX
    //             lastY = area.mouseY
    //             ctx.lineTo(lastX, lastY)
    //             ctx.stroke()
    //         }

    //         MouseArea {
    //             id: area
    //             anchors.fill: parent
    //             acceptedButtons: Qt.LeftButton | Qt.RightButton

    //             onPressed:{
    //                 _vocabCanvas.lastX = mouseX
    //                 _vocabCanvas.lastY = mouseY
    //             }
    //             onPositionChanged: (mouse) => {
    //                 _vocabCanvas.requestPaint()
    //             }
    //             onClicked: console.log("canvas clicked")
    //         }

    //     }
    // }

    AppMsgDialog
    {
        id: _vocabTestConfirmMsgDialog
        anchors.centerIn: parent
        message:"Skip Item?"
        acceptButtonText: "Confirm"
        cancelButtonText: "Cancel"

        onAccepted:skipFunc()
    }
    property string skipItemResult
    function skipFunc(){
        vocabQuiz.vocabReadingTxt = _txtFieldVocabReading.text

        skipItemResult = vocabQuiz.skipItem()

        if(skipItemResult === "next"){
            _txtFieldVocabReading.text = "";
        }
        else if(skipItemResult === "finish"){
            console.log("skipped finished")
            var component = Qt.createComponent("VocabTallyWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_vocabMainWindow);
                if(newWindow){
                    _vocabTestAppWindow.close()
                    newWindow.show()
                }
            }
            else {
                console.log("Error loading component:", component.errorString());
            }
        }
    }
}
