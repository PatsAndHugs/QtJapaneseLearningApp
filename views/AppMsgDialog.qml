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
    width: 400
    height: 200

    contentItem: Rectangle {
        color: "white"
        anchors.fill: parent
        radius: 8

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text {
                id: messageText
                font.pointSize: 18
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
                    font.pointSize: 12
                    onClicked: {
                        _rootDialog.accepted()
                        _rootDialog.close()
                    }
                }

                AppButton {
                    id: cancelButton
                    text: "Cancel"
                    font.pointSize: 12
                    onClicked: {
                        _rootDialog.reject()
                        _rootDialog.close()
                    }
                }
            }
        }
    }


}
