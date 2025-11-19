import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle {
    id:_cardBase
    color: "white"
    radius: 8
    property alias lblTextColor:_wordTypeText.color
    property alias wordType: _wordTypeText.text
    property alias englishMeaning: _textEnglishMeaning.text
    ColumnLayout{
        id:_colLayout
        anchors.fill: parent
        anchors.margins: parent.height *.05
        Text{
            id:_wordTypeText
            color: _colLayout.lblTextColor
            font.pixelSize: 15
            fontSizeMode: Text.Fit
        }

        Text{
            id:_textEnglishMeaning
            Layout.leftMargin: _colLayout.width * .05
            color: _cardBase.lblTextColor
            font.pixelSize: 20
            fontSizeMode: Text.Fit
            Layout.fillWidth: true
            wrapMode: Text.Wrap
        }
    }
}
