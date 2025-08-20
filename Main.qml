import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import JapaneseLearningApp.DbConnectionClass

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

    header: MenuBar{
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
        id:_itemGrad

        GradientStop { position: 0.0; color: "#94DEA5" }

        GradientStop { position: 1.0; color: "#afedcc" }
    }

    Gradient{
        id:_itemGradSelected

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

        delegate: ListItemCard{ id:_wrapper
                                kanjiText: kanji
                                englishMeaningText: kanjienglishname
                                kunyomiText: kunyomi
                                onyomiText: onyomi
                                lblTextColor: ListView.isCurrentItem ? "black" : "black"
                                //mouseAreaOnclick: myListView.currentIndex = index
                                width: myListView.width
                                height: 100
                                gradient: myListView.currentIndex == index ? _itemGradSelected : _itemGrad
                                MouseArea{anchors.fill: parent; onClicked: myListView.currentIndex = index}
        }

        model: KanjiModel
        focus: true
    }

    GridLayout{
        id:_btnGrid
        columns: 3
        //anchors.fill: parent
        anchors.bottom:parent.bottom
        anchors.left:parent.left
        anchors.right:parent.right

        AppBaseBtn{
            id: _selectAllBtn
            text:qsTr("Select Alll")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectAllBtn.hovered ? "white" : "#ffff66"
            font.pointSize: 15
            onClicked: _dbConnClass.populateList()
        }
        AppBaseBtn{
            id: _selectLast5
            text: qsTr("Select Last 5")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectLast5.hovered ? "white" : "#ffff66"
            font.pointSize: 15
        }
        AppBaseBtn{
            id: _selectAllWrong
            text: qsTr("Select All Mistakes")
            Layout.preferredHeight: 100
            Layout.preferredWidth: parent.width / parent.columns
            btnBgColor: _selectAllWrong.hovered ? "white" : "#ffff66"
            font.pointSize: 15
        }

    }

    DbConnClass{
        id: _dbConnClass
    }


}
