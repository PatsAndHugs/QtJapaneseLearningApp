import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
//import "views"

//import JapaneseLearningApp.DbConnectionClass
import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_kanjiMainWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Japanese Learning App")
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
                            kanjiList.clearItems()
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
                        var component = Qt.createComponent("DbConnectionWindow.qml")
                        if(component.status === Component.Ready){
                            var newWindow = component.createObject(_kanjiMainWindow);
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

    FilterKanjiListModel{
        id:_filterModel
        sourceModel: KanjiListModel{
            id:_myModel
            list: kanjiList
            selectionlist: kanjiList
        }
    }

    ListView {
        id: myListView
        anchors.top:_searchInput.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: _btnGrid.top
        anchors.bottomMargin: 95
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        spacing:10
        model: _filterModel

        delegate: KanjiListCard{ id:_wrapper
                                kanjiText: model.kanji
                                englishMeaningText: model.kanjiEnglishName
                                kunyomiText: model.kunyomi
                                onyomiText: model.onyomi
                                lblTextColor: "#023D54"
                                width: myListView.width
                                height: 100
                                color: "white"
                                radioBtnChecked: model.isSelected
                                MouseArea{anchors.fill: parent;
                                    onClicked: {
                                        myListView.currentIndex = index
                                        model.isSelected = !model.isSelected
                                    }
                                }

        }
        focus: true
    }

    TextField {
        id: _searchInput
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        placeholderText: "Search..."
        font.pointSize: 15
        onTextChanged: _filterModel.searchText = _searchInput.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    GridLayout{
        id:_btnGrid
        //anchors.fill: parent
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        columns: 4
        AppButton{
            id: _selectAllBtn
            text:qsTr("Select Alll")
            Layout.preferredHeight: 100
            //Layout.preferredWidth: parent.width / parent.columns
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked: kanjiList.updateAllItemsIsSelected()
        }
        AppButton{
            id: _selectLast5Btn
            text: qsTr("Select Last 5")
            Layout.preferredHeight: 100
            //Layout.preferredWidth: parent.width / parent.columns
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked:kanjiList.updateLastItemIsSelected(5)
        }
        AppButton{
            id: _selectTodayItemsBtn
            text: qsTr("Items For Today")
            Layout.preferredHeight: 100
            //Layout.preferredWidth: parent.width / parent.columns
            Layout.fillWidth: true
            font.pointSize: 15
            onClicked:kanjiList.updateAllCurrentDateItemsIsSelected()
        }
        AppButton{
            id: _confirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: 100
            //Layout.preferredWidth: parent.width / parent.
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
        onClicked: kanjiList.addNewListItems()
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
            if(kanjiList.getSelectedItemsCount() > 0){
                kanjiList.addSelectedItemsToList()
                var component = Qt.createComponent("KanjiTestWindow.qml")
                if(component.status === Component.Ready){
                    var newWindow = component.createObject(_kanjiMainWindow);
                    console.log("confirm")
                    newWindow.show()
                    _kanjiMainWindow.hide()
                }
                kanjiQuiz.getKanjiList(kanjiList.getSelectedItemsList())
            }
        }
        onRejected: console.log("rejected");
    }
}

