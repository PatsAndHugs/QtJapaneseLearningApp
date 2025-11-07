import QtQuick
import QtQuick.Controls.Basic

Button {
    id: _baseBtn
    property alias btnBgColor: _rect.color
    property alias textBottomPadding: _text.bottomPadding
    font.pixelSize: parent.width / 20
    contentItem:Text {
        id: _text
        text: _baseBtn.text
        font: _baseBtn.font
        color: "#023D54"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit
        width: parent.width // Important for fontSizeMode to work
        height: parent.height // Important for fontSizeMode to work
    }

    background: Rectangle{
        id:_rect
        radius: 8
        color: _baseBtn.hovered ? "#ffff66" : "white"
    }
}
