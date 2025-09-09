import QtQuick
Rectangle {
    id:_cardBase
    color: "white"
    radius: 8
    property alias lblTextColor: _textKunyomi.color
    property alias kanjiText: _textKanji.text
    property alias kunyomiText: _textKunyomi.text
    property alias onyomiText: _textOnyomi.text
    property alias englishMeaningText: _textEnglishMeaning.text

    Text{
        id:_textKanji
        color: "black"
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
        color: "black"
        font.pointSize: 15
        horizontalAlignment: Text.AlignJustify
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
    }

    Text{
        id:_textKunyomi
        color: "black"
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 5
        font.pointSize: 20
    }

    Text{
        id:_textOnyomi
        color: "black"
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

}
