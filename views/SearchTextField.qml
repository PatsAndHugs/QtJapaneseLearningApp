import QtQuick
import QtQuick.Controls.Basic
TextField {
    id: _baseTxtField
    property alias backgroundColor: _bgRect.color
    placeholderText: "Search..."
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    background: Rectangle{
        id:_bgRect
        color: backgroundColor
    }
}
