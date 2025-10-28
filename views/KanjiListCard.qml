import QtQuick
import QtQuick.Controls.Basic


Rectangle {
    id:_cardBase
    color: "white"
    radius: 8
    //property alias mouseAreaOnclick: _mouseArea.onClicked
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
    Text{
        id:_textKanji
        color: _cardBase.lblTextColor
        //font.pointSize: 36
        font.pixelSize: Qt.platform.os === "android" ? parent.width / 15 : parent.width / 15
        horizontalAlignment: Text.AlignHCenter
        anchors.left: parent.left
        anchors.leftMargin: 50
        //anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Text{
        id:_textEnglishMeaning
        color: _cardBase.lblTextColor
        //font.pointSize: 15
        font.pixelSize: parent.width / 20
        horizontalAlignment: Text.AlignJustify
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
    }

    Text{
        id:_textKunyomi
        color: _cardBase.lblTextColor
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.20
        //font.pointSize: 20
        font.pixelSize: Qt.platform.os === "android" ? parent.width / 25 : parent.width / 30
    }

    Text{
        id:_textOnyomi
        color: _cardBase.lblTextColor
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.20
        //font.pointSize: 20
        font.pixelSize: Qt.platform.os === "android" ? parent.width / 25 : parent.width / 30
    }

    MouseArea{
        id:_mouseArea
        //anchors.fill: parent
    }

    RadioButton{
        id:_isSelectedRadioBtn
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: _cardBase.height * 0.3
        anchors.rightMargin: _cardBase.height * 0.1

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
