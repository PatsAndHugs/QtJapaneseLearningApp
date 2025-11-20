import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import VocabClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_learnVocabMainWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Study Vocab Window")
    color:"#023D54"

    LogInPopUp{
        id:_loginPopup
    }

    Component.onCompleted: {
        if (Qt.platform.os === "android") {
            _learnVocabMainWindow.width = Screen.width
            _learnVocabMainWindow.height = Screen.height
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
                        _learnVocabMainWindow.close()
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
        id: _vocabListView
        anchors.top:_searchInput.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottomMargin: 95
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        spacing:10
        height: Qt.platform.os === "android" ? parent.height * 0.50 : parent.height * 0.75//parent.height * .75
        model: _vocabFilterModel

        delegate: KanjiListCard{ id:_wrapper
                                kanjiText: model.vocabKanji
                                kunyomiText: model.vocabMeaning
                                onyomiText: model.vocabReading
                                lblTextColor: "#023D54"
                                width: _vocabListView.width
                                height: Qt.platform.os === "android" ? _vocabListView.height * 0.20 : _vocabListView.height * 0.12
                                color: "white"
                                radioBtnChecked: model.isSelected
                                MouseArea{anchors.fill: parent;
                                    onClicked: {
                                        _vocabListView.currentIndex = index
                                        model.isSelected = !model.isSelected
                                        vocabList.setItemToShowInLearnWindow()
                                    }
                                }
        }
        focus: true
    }

    SearchTextField {
        id: _searchInput
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        placeholderText: "Search..."
        font.pixelSize: parent.width / 20
        onTextChanged: _filterModel.searchText = _searchInput.text
        height: parent.height * .05
        backgroundColor: "white"
    }


    RoundButton{
        id:_addBtn
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 200
        anchors.rightMargin: 20
        width: parent.width / 10
        height: parent.width / 10
        onClicked: vocabList.addNewListItems()
        opacity: 0.9

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#023D54"
            text: "\u002B"
            font.pixelSize: parent.width * 0.5
        }
    }

    Connections{
        target: vocabList
        function onVocabDetailsListChanged(){
            var component = Qt.createComponent("LearnVocabWindow.qml")
            if(component.status === Component.Ready){
                var newWindow = component.createObject(_learnVocabMainWindow);
                newWindow.show()
                _learnVocabMainWindow.hide()
            }
        }
    }
}

