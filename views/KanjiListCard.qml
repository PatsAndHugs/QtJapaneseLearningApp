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
        font.pointSize: 36
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
        font.pointSize: 15
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
        anchors.topMargin: 5
        font.pointSize: 20
    }

    Text{
        id:_textOnyomi
        color: _cardBase.lblTextColor
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pointSize: 20
    }

    MouseArea{
        id:_mouseArea
        //anchors.fill: parent
    }

    RadioButton{
        id:_isSelectedRadioBtn
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.rightMargin: 10

        indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 40
                radius: 10 // Makes it circular
                border.color: _isSelectedRadioBtn.checked ? "#e6e657" : "#023D54"// Border color based on checked state
                border.width: 2

                Rectangle {
                    id:_kanjiListCardRadioBtnCenter
                    anchors.centerIn: parent
                    width: parent.width * 0.6
                    height: parent.height - 10
                    radius: width / 2
                    color: _isSelectedRadioBtn.checked ? "#e6e657" : "#023D54" // Inner circle color when checked
                    //visible: _isSelectedRadioBtn.checked // Only visible when checked
                }
            }
    }

}
