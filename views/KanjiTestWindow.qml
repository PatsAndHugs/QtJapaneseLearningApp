import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

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

        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        columns: 2
        rowSpacing: 20

        Label{
            id:_lblKanji
            color: "black"
            font.pointSize: 50
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignCenter
            text:qsTr("月")
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
            text:qsTr("moon, month")
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
        }
        Button{
            id: _skipBtn
            text: qsTr("Skip")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            //color: _confirmBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            Layout.rightMargin: 10

        }

    }
}
