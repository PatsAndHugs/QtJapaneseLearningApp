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

    ColumnLayout{
        id:_tallyColLayout
        anchors.fill: parent

        RowLayout{
            id:_scoreRowLayout
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 50
            Rectangle{
                id: _KanjiTallyCorrectContainer
                color: "lightblue"
                Layout.preferredHeight: 80
                Layout.fillWidth: true
                Layout.leftMargin: 10
                radius: 8
                Label{
                    text: qsTr("Correct Answers: ")
                    color: "#023D54"
                    font.pointSize: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label{
                    text: kanjiQuiz.getCorrectScore()
                    color: "#023D54"
                    font.pointSize: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle{
                id: _KanjiTallyIncorrectContainer
                color: "#ff7057"
                Layout.preferredHeight: 80
                Layout.fillWidth: true
                Layout.rightMargin: 10
                radius: 8
                Label{
                    text: qsTr("Wrong Answers: ")
                    color: "#023D54"
                    font.pointSize: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label{
                    text: kanjiQuiz.getIncorrectScore()
                    color: "#023D54"
                    font.pointSize: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
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
                lblTextColor: "#023D54"
                width: _listView.width
                height: 100
                radioBtnColor: model.isAnswerCorrect ? "blue" : "red"
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

            AppButton{
                text:qsTr("Return To Main Menu")
                Layout.preferredHeight: 100
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                font.pointSize: 20
                onClicked: {
                     _tallyAppWindow.close()
                    kanjiQuiz.clearQuizList()
                    kanjiList.updateListDatesAfteResult(kanjiQuiz.getKanjiListToUpdate())
                    _kanjiMainWindow.show()
                }
            }
        }
    }


}
