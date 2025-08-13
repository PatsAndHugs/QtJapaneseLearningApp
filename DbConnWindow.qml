import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform 1.1
import JapaneseLearningApp.DbConnectionClass
import QtQuick.Dialogs

ApplicationWindow {

    width: 350
    height: 300
    visible: true
    title: qsTr("Connectiion Window")
    color:"#023D54"

    DbConnClass{
        id:_dbConnClass
    }

    GridLayout{
        id:_gridLayout
        columns: 2
        anchors.horizontalCenter: parent.horizontalCenter
        y: 80
        Label{
            text:qsTr("Username:")
            color: "white"
            Layout.preferredHeight: 20
        }

        TextField{
            id:_usernameTxtField
            placeholderText: qsTr("Enter Username...")
            Layout.preferredHeight: 20
        }

        Label{
            text:qsTr("Password:")
            color: "white"
            Layout.preferredHeight: 20
        }

        TextField{
            id:_passwordTxtField
            placeholderText: qsTr("Enter Password...")
            Layout.preferredHeight: 20
        }

        TextField{
            id:_fileDiagTxtField
            Layout.columnSpan: 2
            Layout.fillWidth: true
            placeholderText: qsTr("Enter key file path...")
            Layout.preferredHeight: 20
            Button{
                id:_fileDialogBtn
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 30
                text:qsTr(". . .")
                onClicked: _fileDialog.open()
            }
        }

        CheckBox{
            id:_rememberCheckBox
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
            text: "Remember Path"
            checkState: Qt.Unchecked
            onCheckedChanged: {
                console.log("checkbox is", checked)
            }
        }

        Button{
            id:_connWindowBtn
            Layout.topMargin: 10
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            text:qsTr("Save")
            onClicked: textFieldCheck()
        }

        MessageDialog {
            id:_dialog
            title:"Message"
            text: "No File Path Selected"
            buttons: MessageDialog.Ok
        }

    }

    FileDialog{
        id:_fileDialog
        title: qsTr("Select File")
        nameFilters: ["XML files (*.xml)"]
        //selectedNameFilter:"All files(*)"

        onAccepted: {
            console.log("Selecred file " + _fileDialog.currentFile)
            _fileDiagTxtField.text = _fileDialog.currentFile
        }
    }

    function textFieldCheck()
    {
        if(_fileDiagTxtField.text !== "")
            saveConnFilePath()
        else
            _dialog.open()
    }

    function saveConnFilePath()
    {
        _dbConnClass.configFilePath = _fileDiagTxtField.text
        _dbConnClass.loadXmlFile()
        _dbConnClass.setupConn()
        if(_rememberCheckBox.checkState === Qt.Checked){
            _dbConnClass.saveFilePathToXml()
        }
    }

}


