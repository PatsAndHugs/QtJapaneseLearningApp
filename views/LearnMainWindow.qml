import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_learnMainWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Study Kanji Window")
    color:"#023D54"

    LogInPopUp{
        id:_loginPopup
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
                        _learnMainWindow.close()
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
        id: _learnListView
        anchors.top:_searchInput.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
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
                                width: _learnListView.width
                                height: 100
                                color: "white"
                                radioBtnChecked: model.isSelected
                                MouseArea{anchors.fill: parent;
                                    onClicked: {
                                        _learnListView.currentIndex = index
                                        model.isSelected = !model.isSelected
                                        var component = Qt.createComponent("LearnKanjiWindow.qml")
                                        if(component.status === Component.Ready){
                                            var newWindow = component.createObject(_learnMainWindow);
                                            kanjiList.setItemToShowInLearnWindow()
                                            newWindow.show()
                                            _learnMainWindow.hide()
                                        }
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


    RoundButton{
        id:_addBtn
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
        id: _learnConfirmMsgDialog
        anchors.centerIn: parent
        message:"Confirm Selection?"
        acceptButtonText: "Confirm"
        cancelButtonText: "Cancel"

        onAccepted: {
            if(kanjiList.getSelectedItemsCount() > 0){
                kanjiList.addSelectedItemsToList()
                var component = Qt.createComponent("KanjiTestWindow.qml")
                if(component.status === Component.Ready){
                    var newWindow = component.createObject(_learnMainWindow);
                    console.log("confirm")
                    newWindow.show()
                    _learnMainWindow.hide()
                }
                kanjiQuiz.getKanjiList(kanjiList.getSelectedItemsList())
            }
        }
        onRejected: console.log("rejected");
    }
}

