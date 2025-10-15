import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_registerWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Register")
    color:"#023D54"

    GridLayout{
        anchors.centerIn: parent
        columns: 2
        width: parent.width / 1.8
        Label{
            text:qsTr("Username:")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 20
            color: "white"
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        TextField{
            id:_usernameTxtField
            placeholderText: qsTr("Enter Username...")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 15
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        Label{
            text:qsTr("Password:")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 20
            color: "white"
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        TextField{
            id:_passwordTxtField
            placeholderText: qsTr("Enter Password...")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 15
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        Label{
            text:qsTr("Email:")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 20
            color: "white"
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        TextField{
            id:_emailTxtField
            placeholderText: qsTr("Enter Email Address...")
            horizontalAlignment: TextInput.AlignHCenter
            font.pointSize: 15
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        Button{
            text: qsTr("Register")
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.columnSpan: 2
            onClicked:{
                userLogin.username = _usernameTxtField.text
                userLogin.password = _passwordTxtField.text
                userLogin.email = _emailTxtField.text
                userLogin.registerUser()
            }
            Connections{
                target:userLogin
                function onRegisterFinished(){
                    if(userLogin.getRegisterResult() === true)
                    {
                        console.log("Register Successful")
                        var component = Qt.createComponent("LoginWindow.qml")
                        if(component.status === Component.Ready){
                            var newWindow = component.createObject(_registerWindow);
                            if(newWindow){
                                _registerWindow.close()
                                newWindow.show()
                            }
                        }
                    }
                    else
                        console.log("Register Failed")
                }
            }
        }

        Button{
            text: qsTr("Back To Login")
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.columnSpan: 2
            onClicked: {
                //_registerPopup.open()
                //_loginPopup.close()
                // userLogin.username = _usernameTxtField.text
                // userLogin.password = _passwordTxtField.text
                // userLogin.registerUser();
            }
        }
    }

}
