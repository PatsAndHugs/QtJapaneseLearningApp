import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import VocabClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_vocabMainWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Vocabulary Main Window")
    color:"#023D54"

    LogInPopUp{
        id:_loginPopup
    }

    header: MenuBar{
        MenuBarItem{
            text: qsTr("User")
            onTriggered:{
                console.log("triggered");
                if(userLogin.getLoginStatus() === true)
                    _userMenuItem.text ="Logout"
                else
                    _userMenuItem.text ="Login"
            }
            menu:Menu{
                MenuItem{
                    id:_userMenuItem
                    text: qsTr("Login")
                    onClicked:{

                        if(userLogin.getLoginStatus() === true){
                            vocabList.clearItems()
                            dbConn.logoutUser()
                        }
                        else{
                            _loginPopup.open()
                        }
                    }
                }
                MenuItem{text:"Exit"}
            }
        }

        MenuBarItem{
            text: qsTr("Connection Config")
            menu:Menu {
                id:_menu
                MenuItem{
                    text:"Edit Connection"
                    onClicked:{
                        var component = Qt.createComponent("DbConnWindow.qml")
                        if(component.status === Component.Ready){
                            var newWindow = component.createObject(_vocabMainWindow);
                            newWindow.show()
                        }
                        else
                            console.log("Error loading component:",component.errorString())
                    }
                }

                MenuItem{text:"Exit"}
            }

        }
    }

    FilterVocabListModel{
        id:_vocabFilterModel
        sourceModel: VocabListModel{
            list: vocabList
            selectionlist: vocabList
        }
    }

    ListView {
        id: vocabListView
        anchors.top:_vocabSearchInput.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: _vocabBtnGrid.top
        anchors.bottomMargin: 95
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        spacing:10
        model: _vocabFilterModel

        delegate: KanjiListCard{ id:_wrapper
                                kanjiText: model.vocabKanji
                                //englishMeaningText: model.
                                kunyomiText: model.vocabMeaning
                                onyomiText: model.vocabReading
                                lblTextColor: "#023D54"
                                width: vocabListView.width
                                height: 100
                                color: "white"
                                radioBtnChecked: model.isSelected
                                MouseArea{anchors.fill: parent;
                                    onClicked: {
                                        vocabListView.currentIndex = index
                                        model.isSelected = !model.isSelected
                                    }
                                }

        }
        focus: true
    }

    TextField {
        id: _vocabSearchInput
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        placeholderText: "Search..."
        font.pointSize: 15
        onTextChanged: _vocabFilterModel.searchText = _vocabSearchInput.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    GridLayout{
        id:_vocabBtnGrid
        //anchors.fill: parent
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        columns: 4
        AppButton{
            text:qsTr("Select Alll")
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked: vocabList.updateAllItemsIsSelected()
        }
        AppButton{
            text: qsTr("Select Last 5")
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked:vocabList.updateLastItemIsSelected(5)
        }
        AppButton{
            text: qsTr("Items For Today")
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked:vocabList.updateAllCurrentDateItemsIsSelected()
        }
        AppButton{
            text: qsTr("Confirm")
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked:_mainConfirmMsgDialog.open()
        }
    }

    RoundButton{
        id:_addBtn
        //text: "\u002B"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 200
        anchors.rightMargin: 20
        width:100; height: 100
        onClicked: vocabList.addNewListItems()
        opacity: 0.9

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#023D54"
            text: "\u002B"
            font.pointSize: 30
        }
    }

    AppMsgDialog
    {
        id: _mainConfirmMsgDialog
        anchors.centerIn: parent
        message:"Confirm Selection?"
        acceptButtonText: "Confirm"
        cancelButtonText: "Cancel"

        onAccepted: {
            if(vocabList.getSelectedItemsCount() > 0){
                vocabList.addSelectedItemsToList()
                var component = Qt.createComponent("VocabTestWindow.qml")
                if(component.status === Component.Ready){
                    var newWindow = component.createObject(_vocabMainWindow);
                    console.log("confirm")
                    newWindow.show()
                    _vocabMainWindow.hide()
                }
                vocabQuiz.getVocabList(vocabList.getSelectedItemsList())
            }
        }
        onRejected: console.log("rejected");
    }
}

