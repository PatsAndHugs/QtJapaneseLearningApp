import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_loginWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Login")
    color:"#023D54"

    property bool loginSwitchState: false
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

        AppSwitchCtrl{
            id:_loginSwitch
            switchText: "Keep Login"
            switchChecked: false
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: _passwordTxtField.width / 2
            Layout.columnSpan: 2
            Layout.preferredHeight: 40
            onToggle:{
                loginSwitchState = !loginSwitchState
                userLogin.checkboxState = loginSwitchState
            }
        }

        Button{
            id:_loginBtn
            text: qsTr("Login")
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.columnSpan: 2
            onClicked:{
                userLogin.username = _usernameTxtField.text
                userLogin.password = _passwordTxtField.text
                if(_usernameTxtField.text !== "" && _passwordTxtField.text !== "")
                {
                    _loginBtn.enabled = false
                    userLogin.checkLoginResult()
                }
            }
            Connections{
                target:userLogin
                function onUserLoginResultReceived(){
                    if(userLogin.getLoginResult() === true)
                    {
                        console.log("Login Successful")
                        var componentMain = Qt.createComponent("../Main.qml")
                        if(componentMain.status === Component.Ready){
                            var newWindowMain = componentMain.createObject(_loginWindow);
                            if(newWindowMain){
                                _loginWindow.close()
                                newWindowMain.show()
                            }
                        }
                    }
                    else
                    {
                        _loginBtn.enabled = true
                        console.log("Login Failed")
                    }
                }
            }
        }

        Button{
            text: qsTr("Register")
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            Layout.columnSpan: 2
            onClicked: {
                var component = Qt.createComponent("RegisterWindow.qml")
                if(component.status === Component.Ready){
                    var newWindow = component.createObject(_loginWindow);
                    if(newWindow){
                        _loginWindow.close()
                        newWindow.show()
                    }
                }
            }
        }
    }
}
