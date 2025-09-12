import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: _loginPopup
    width: 500
    height: 500
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    Rectangle
    {
        anchors.fill: parent
        color: "#023D54"
    }
    Button{
        height: 50
        width: 50
        anchors.right: parent.right
        onClicked: _loginPopup.close()
    }

    GridLayout{
        columns: 2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 130

        Label{
            text:qsTr("Username:")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 20
            color: "white"
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width / parent.columns
        }

        TextField{
            id:_usernameTxtField
            placeholderText: qsTr("Enter Username...")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 15
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            Layout.alignment: Qt.AlignHCenter
        }

        Label{
            text:qsTr("Password:")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 20
            color: "white"
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width / parent.columns
        }

        TextField{
            id:_passwordTxtField
            placeholderText: qsTr("Enter Password...")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 15
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            Layout.alignment: Qt.AlignHCenter
        }

        Button{
            text: qsTr("Login")
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
            onClicked:{
                userLogin.username = _usernameTxtField.text
                userLogin.password = _passwordTxtField.text
                if(userLogin.loginResult() === true)
                {
                    console.log("Login Successful")
                    kanjiList.addItems()
                }
                else
                    console.log("Login Failed")
            }
        }

        Button{
            text: qsTr("Register")
            Layout.preferredHeight: 50
            Layout.preferredWidth: parent.width / parent.columns
        }

    }

    Overlay.modal: Rectangle {
                color: "#80000000" // Semi-transparent black (adjust color and opacity as desired)
            }
    focus: true
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
}

