import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Effects
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

    ColumnLayout{
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        Image {
            id: _mainImg
            source: "qrc:/image/resources/Ryza_and_the_holy_tower_of_Pynnor.png"
            fillMode: Image.PreserveAspectCrop // Adjust as needed
            Layout.preferredHeight: parent.height / 2
            Layout.fillWidth: true
        }

        Label{
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            text: "Silence Suzuka"
            font.pointSize: 30
            font.bold: true
        }

        AppButton{
           text: "Learn"
           Layout.preferredHeight: 100
           Layout.fillWidth: true
           font.pointSize: 15

        }
        AppButton{
           text: "Kanji Test"
           Layout.preferredHeight: 100
           Layout.fillWidth: true
           font.pointSize: 15
           onClicked:{
               var component = Qt.createComponent("views/KanjiMainWindow.qml")
               if(component.status === Component.Ready){
                   var newWindow = component.createObject(_mainAppWindow);
                   if(newWindow){
                       console.log("clicked")
                        _mainAppWindow.close()
                       newWindow.show()
                   }
               }
           }

        }
        AppButton{
           text: "Vocab Test"
           Layout.preferredHeight: 100
           Layout.fillWidth: true
           font.pointSize: 15
           onClicked:{
               var component = Qt.createComponent("views/VocabMainWindow.qml")
               if(component.status === Component.Ready){
                   var newWindow = component.createObject(_mainAppWindow);
                   if(newWindow){
                       console.log("clicked")
                        _mainAppWindow.close()
                       newWindow.show()
                   }
               }
           }
        }
    }

}

