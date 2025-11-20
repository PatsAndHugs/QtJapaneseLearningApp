import QtQuick
import QtQuick.Controls.Basic


Dialog {

    id:_rootDialog


    property alias message: messageText.text
    property alias acceptButtonText: acceptButton.text
    property alias cancelButtonText: cancelButton.text

    // Signal to emit when the dialog is accepted
    //signal accepted()
    // Signal to emit when the dialog is cancelled
   // signal cancelled()

    modal: true
    width: parent.width * .5
    height: parent.height * .2

    contentItem: Rectangle {
        color: "white"
        anchors.fill: parent
        radius: 8

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text {
                id: messageText
                font.pixelSize: Qt.platform.os === "android" ? parent.width * .15 : parent.width * .1
                fontSizeMode: Text.Fit
                font.bold: true
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                width: _rootDialog.width - 40 // Adjust width to prevent overflow
                color: "#023D54"
            }

            Row {
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                AppButton {
                    id: acceptButton
                    text: "OK"
                    font.pixelSize: _rootDialog.width * .05
                    onClicked: {
                        _rootDialog.accepted()
                        _rootDialog.close()
                    }
                }

                AppButton {
                    id: cancelButton
                    text: "Cancel"
                    font.pixelSize: _rootDialog.width * .05
                    onClicked: {
                        _rootDialog.reject()
                        _rootDialog.close()
                    }
                }
            }
        }
    }


}
