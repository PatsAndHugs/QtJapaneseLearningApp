import QtQuick
import QtQuick.Controls.Basic

Button {
    id: _baseBtn
    property alias btnBgColor: _rect.color

    contentItem:Text {
        id: _text
        text: _baseBtn.text
        font: _baseBtn.font
        color: "#023D54"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle{
        id:_rect
        radius: 8
    }
}
