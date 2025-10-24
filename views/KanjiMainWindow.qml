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

    Component.onCompleted: {
        if (Qt.platform.os === "android") {
            _kanjiMainWindow.width = Screen.width
            _kanjiMainWindow.height = Screen.height
        }
    }

    header: MenuBar{
        MenuBarItem{
            text: qsTr("Menu")
            menu:Menu{
                MenuItem{
                    id:_userMenuItem
                    text: qsTr("Return To Main Menu")
                    onClicked:{
                        _mainAppWindow.show()
                        _kanjiMainWindow.destroy()
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
        font.pixelSize: parent.width / 20
        onTextChanged: _filterModel.searchText = _searchInput.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    RowLayout{
        id:_btnGrid
        //anchors.fill: parent
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        height: parent.height / 10
        AppButton{
            id: _selectAllBtn
            text:qsTr("Select All")
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width / 4.2
            //Layout.fillWidth: true
            onClicked: kanjiList.updateAllItemsIsSelected()
        }
        AppButton{
            id: _selectLast5Btn
            text: qsTr("Select Last 5")
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width / 4.2
            //Layout.fillWidth: true
            onClicked:kanjiList.updateLastItemIsSelected(5)
        }
        AppButton{
            id: _selectTodayItemsBtn
            text: qsTr("Items For Today")
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width / 4.2
            //Layout.fillWidth: true
            onClicked:kanjiList.updateAllCurrentDateItemsIsSelected()
        }
        AppButton{
            id: _confirmBtn
            text: qsTr("Confirm")
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width / 4.2
            //Layout.fillWidth: true
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
        width: parent.width / 10
        height: parent.width / 10
        onClicked: kanjiList.addNewListItems()
        opacity: 0.9

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#023D54"
            text: "\u002B"
            font.pixelSize: parent.width / 10
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

