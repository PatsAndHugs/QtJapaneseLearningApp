import QtQuick

Window {

    ///COLOR SCHEME #023D54 #9A6735 #94DEA5 #ffff66
    width: 720
    height: 1280
    visible: true
    title: qsTr("Japanese Learning App")
    color:"#023D54"

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
        width: (parent.width / 2) - 50; height: parent.height / 2
        anchors.centerIn: parent
        spacing:10
        delegate: Rectangle {

            id: wrapper
            width: 300
            height: contactInfo.height * 5
            radius: 8
            //color: ListView.isCurrentItem ? "#5ee527" : "#87ea55"
            //Behavior on color { ColorAnimation { duration: 100 } }

            //color: myListView.currentIndex === index ? "#ffff66" : "#94DEA5"
            gradient: myListView.currentIndex == index ? _itemGradSelected : _itemGrad

            Text {
                id: contactInfo
                text: name + ": " + number
                color: wrapper.ListView.isCurrentItem ? "black" : "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: myListView.currentIndex = index
            }
        }

        model: ModelTest {}

        focus: true
    }


}
