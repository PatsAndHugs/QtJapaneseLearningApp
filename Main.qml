import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import "views"

//import JapaneseLearningApp.DbConnectionClass
import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_mainAppWindow
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
            text: qsTr("LogIn")
            menu:Menu{
                MenuItem{
                    text: qsTr("Login")
                    onClicked:{
                        _loginPopup.open()
                    }
                }
                MenuItem{
                    text:"Logout"
                    onClicked:{
                        kanjiList.clearItems()
                        dbConn.logoutUser()
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
                            var newWindow = component.createObject(_mainAppWindow);
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

    Gradient{
        id:_itemGradSelected

        GradientStop { position: 0.0; color: "#94DEA5" }

        GradientStop { position: 1.0; color: "#afedcc" }
    }

    Gradient{
        id:_itemGrad

        GradientStop { position: 0.0; color: "#ffff66" }

        GradientStop { position: 1.0; color: "#e3ffbf" }
    }

    ListView {
        id: myListView
        //width: (parent.width / 2) - 50; height: parent.height / 2
        //width:500; height:500
        // anchors.right: parent.right
        // anchors.left: parent.left
        // anchors.top: parent.top
        anchors.fill: parent
        spacing:10
        model: KanjiListModel{
            id:_myModel
            list: kanjiList
            selectionlist: kanjiList
        }

        delegate: ListItemCard{ id:_wrapper
                                kanjiText: model.kanji
                                englishMeaningText: model.kanjiEnglishName
                                kunyomiText: model.kunyomi
                                onyomiText: model.onyomi
                                lblTextColor: ListView.isCurrentItem ? "black" : "black"
                                width: myListView.width
                                height: 100
                                gradient: model.isSelected ? _itemGradSelected : _itemGrad
                                MouseArea{anchors.fill: parent;
                                    onClicked: {
                                        myListView.currentIndex = index
                                        model.isSelected = !model.isSelected
                                    }
                                }

        }
        focus: true
    }

    GridLayout{
        id:_btnGrid

        //anchors.fill: parent
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        columns: 4
        AppBaseBtn{
            id: _selectAllBtn
            text:qsTr("Select Alll")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectAllBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            onClicked: kanjiList.updateAllItemsIsSelected()
        }
        AppBaseBtn{
            id: _selectLast5Btn
            text: qsTr("Select Last 5")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectLast5Btn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            onClicked:kanjiList.updateLastItemIsSelected(5)
        }
        AppBaseBtn{
            id: _selectAllWrongBtn
            text: qsTr("Select All Mistakes")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectAllWrongBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            onClicked:kanjiList.clearItems()
        }
        AppBaseBtn{
            id: _confirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _confirmBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            onClicked:{
                if(kanjiList.getSelectedItemsCount() > 0){
                    kanjiList.addSelectedItemsToList()
                    var component = Qt.createComponent("views/KanjiTestWindow.qml")
                    if(component.status === Component.Ready){
                        var newWindow = component.createObject(_mainAppWindow);
                        newWindow.show()
                        _mainAppWindow.hide()
                    }
                    kanjiQuiz.getKanjiList(kanjiList.getSelectedItemsList())
                }
            }

        }
    }
}

