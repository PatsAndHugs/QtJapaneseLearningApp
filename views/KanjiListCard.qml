import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle {
    id:_cardBase
    color: "white"
    radius: 8
    property alias lblTextColor:_textKunyomi.color

    property alias kanjiText: _textKanji.text
    property alias kunyomiText: _textKunyomi.text
    property alias onyomiText: _textOnyomi.text
    property alias englishMeaningText: _textEnglishMeaning.text
    property alias radioBtnChecked: _isSelectedRadioBtn.checked
    property alias radioBtnColor: _kanjiListCardRadioBtnCenter.color

    // Image {
    //     id: _img
    //     source: "qrc:/image/resources/silencesuzuka.png"
    //     width:50
    //     height:50
    //     //fillMode: Image.PreserveAspectFit
    // }

    GridLayout{
        id:_cardGrid
        anchors.fill: parent
        //anchors.margins: parent.height * .05
        columns:3
        rows:6
        Text{
            id:_textKanji
            color: _cardBase.lblTextColor
            Layout.column: 0
            Layout.row: 0
            Layout.rowSpan: 3
            Layout.maximumWidth: 100
            Layout.maximumHeight: 50
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: Qt.platform.os === "android" ? parent.width / 15 : parent.width / 15
            fontSizeMode: Text.Fit
            Layout.leftMargin: parent.width * .02
        }

        Text{
            id:_textEnglishMeaning
            Layout.column: 0
            Layout.row:3
            Layout.rowSpan: 2
            color: _cardBase.lblTextColor
            Layout.alignment: Qt.AlignCenter
            Layout.maximumWidth: 100
            Layout.maximumHeight: 30
            font.pixelSize: Qt.platform.os === "android" ? 10 : 20
            fontSizeMode: Text.Fit
        }

        Text{
            id:_textKunyomi
            Layout.column: 1
            Layout.row:0
            Layout.rowSpan: 3
            color: _cardBase.lblTextColor
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: parent.width * .7
            Layout.preferredHeight: parent.height * .5
            Layout.maximumHeight: 30
            font.pixelSize: Qt.platform.os === "android" ? 10 : 20
            fontSizeMode: Text.Fit
        }

        Text{
            id:_textOnyomi
            Layout.column: 1
            Layout.row:3
            Layout.rowSpan: 3
            color: _cardBase.lblTextColor
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: parent.width * .7
            Layout.preferredHeight: parent.height * .5
            Layout.maximumHeight: 30
            font.pixelSize: Qt.platform.os === "android" ? 10 : 20
            fontSizeMode: Text.Fit
        }

        RadioButton{
            id:_isSelectedRadioBtn
            Layout.column: 2
            Layout.rowSpan: 6
            //Layout.fillHeight: true
            //Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Layout.maximumWidth: 100
            Layout.maximumHeight: parent.height
            indicator: Rectangle {
                    implicitWidth: _cardBase.height / 5
                    implicitHeight: _cardBase.height / 2.5
                    radius: 10 // Makes it circular
                    border.color: _isSelectedRadioBtn.checked ? "#e6e657" : "#023D54"// Border color based on checked state
                    border.width: 2

                    Rectangle {
                        id:_kanjiListCardRadioBtnCenter
                        anchors.centerIn: parent
                        width: parent.width * 0.6
                        height: parent.height * 0.8
                        radius: width / 2
                        color: _isSelectedRadioBtn.checked ? "#e6e657" : "#023D54" // Inner circle color when checked
                        //visible: _isSelectedRadioBtn.checked // Only visible when checked
                    }
                }
        }
    }
}
