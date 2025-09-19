import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item{
    id:_customSwitchRoot
    property alias switchText: _customSwitchTxt.text
    property alias switchChecked: _customSwitch.checked

    signal toggle()
    RowLayout{
        Text {
            id: _customSwitchTxt
            text: _customSwitchRoot.switchText
            color: "white"
            font.pointSize: 8
            //anchors.verticalCenter: _customSwitchRoot.verticalCenter
            //anchors.left: _customSwitchRoot.left
            //anchors.leftMargin: -50
        }
        Switch {

                id: _customSwitch

                // Customize the background
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 30
                    radius: 15
                    color: _customSwitch.checked ? "#ffff66" : "white"
                    border.color: _customSwitch.checked ? "darkgreen" : "gray"
                    border.width: 1
                }

                // Customize the indicator (the movable part)
                indicator: Rectangle {
                    implicitWidth: 26
                    implicitHeight: 26
                    radius: 13
                    color: "white"
                    x: _customSwitch.checked ? parent.width - width - 2 : 2 // Adjust x-position based on checked state
                    anchors.verticalCenter: parent.verticalCenter
                    border.color: "lightgray"
                    border.width: 1
                }

        }
    }

    Component.onCompleted: {
        _customSwitch.toggled.connect(_customSwitchRoot.toggle)
    }


}






