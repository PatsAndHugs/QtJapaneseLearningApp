import QtQuick

Rectangle {
    id:_cardBase
    color: "black"
    radius: 8
    //property alias mouseAreaOnclick: _mouseArea.onClicked
    property alias lblTextColor: _text.color
    property alias lblText: _text.text

    Image {
        id: _img
        source: "qrc:/image/resources/silencesuzuka.png"
        width:50
        height:50
        //fillMode: Image.PreserveAspectFit
    }

    Text{
        id:_text
        color: "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }

    MouseArea{
        id:_mouseArea
        //anchors.fill: parent
    }

}
