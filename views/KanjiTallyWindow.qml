import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import KanjiClass 1.0

ApplicationWindow {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    id:_mainAppWindow
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

    ListView {
        id:_listView
        anchors.fill: parent
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
            width: myListView.width
            height: 100
            gradient: model.isAnswerCorrect ? _itemCorrect : _itemWrong

        }
    }
}
