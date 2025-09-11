import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_tallyAppWindow
    width: 720
    height: 1280
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Kanji Test")
    color:"#023D54"

    Gradient{
        id:_itemCorrect

        GradientStop { position: 0.0; color: "#076AF5" }

        GradientStop { position: 1.0; color: "#B1CCF2" }
    }

    Gradient{
        id:_itemWrong

        GradientStop { position: 0.0; color: "#E35036" }

        GradientStop { position: 1.0; color: "#F2CDB1" }
    }
    ColumnLayout{
        id:_tallyColLayout
        anchors.fill: parent

        RowLayout{
            id:_scoreRowLayout
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 50
            Label{
                text: qsTr("Correct: ")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter
            }
            Label{
                text: qsTr("100")
                font.pointSize: 20
                Layout.alignment: Qt.AlignLeft
            }
            Label{
                text: qsTr("Wrong: ")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter
            }
            Label{
                text: qsTr("100")
                font.pointSize: 20
                Layout.alignment: Qt.AlignLeft
            }

        }

        ListView {
            id:_listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 100
            Layout.rightMargin: 20
            Layout.leftMargin: 20
            spacing: 10

            model: KanjiQuizResultModel{
                id:_model
                dataList: kanjiQuiz.getResultList()
            }

            delegate: KanjiListCard{
                id:_wrapper
                kanjiText: model.kanji
                englishMeaningText: model.kanjiEnglishMeaning
                kunyomiText: model.kunyomi
                onyomiText: model.onyomi
                lblTextColor: ListView.isCurrentItem ? "black" : "black"
                width: _listView.width
                height: 100
                gradient: model.isAnswerCorrect ? _itemCorrect : _itemWrong

            }
        }

        RowLayout{
            id:_scoreBtnRowLayout
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 50
            Layout.rightMargin: 40
            Layout.leftMargin: 40

            Button{
                text:qsTr("Return To Main Menu")
                Layout.preferredHeight: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                font.pointSize: 20
                onClicked: {
                     _tallyAppWindow.close()
                    kanjiQuiz.clearQuizList()
                    _mainAppWindow.show()
                }
            }
        }
    }


}
