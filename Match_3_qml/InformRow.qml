import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle{
    //border.color: "black"
    color: Qt.lighter("yellow")
    z:1
    //radius: 10
    function font_size(_width, _height){
        return _width > _height ? _height / 1.5 : _width / 1.5;
    }

    Rectangle{
        id: rectMoveText
        width: parent.width/ 6
        height: parent.height / 2
        color: Qt.lighter("yellow")
        anchors.right: rectMainButton.left
        anchors.verticalCenter: parent.verticalCenter
        Text{
            id: staticMove
            height: parent.height / 2.1
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Move :")
            font.pixelSize: font_size(parent.width, parent.height)
        }
        Item{
            id: voidItem
            height: parent.height / 10
            anchors.top: staticMove.bottom
        }
        Text{
            anchors.top: voidItem.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: move_count
            font.pixelSize: font_size(parent.width, parent.height)
        }
    }

    Rectangle {
        id: rectMainButton
        anchors.centerIn: parent
        width: parent.height * 2
        height: parent.height / 2
        color: Qt.lighter("yellow")
        Button{
            id: main_restart_button
            width: parent.width * 0.7
            height: parent.height
            anchors.centerIn: parent
            anchors.topMargin: height / 1.5
            Text{
                text: "Restart"
                anchors.centerIn: parent
                font.pixelSize: font_size(parent.width, parent.height)
            }
            background :Rectangle{
                gradient: Gradient {
                    GradientStop { position: 0.0; color: main_restart_button.pressed ? Qt.lighter("#F28C28") : Qt.lighter("orange")}
                    GradientStop { position: 1.0; color: main_restart_button.pressed ? "#F28C28" : "orange"}
                }
                border.color: "black"
                radius: 30
            }
            onClicked: {
                myGrid.listModel.start_shuffle();
                root.score_count = 0;
                root.move_count = 0;
                quit.focus = true;
            }
        }
    }

    Rectangle{
        id: rectScoreText
        width: parent.width/ 6
        height: parent.height / 2
        color: Qt.lighter("yellow")
        anchors.left: rectMainButton.right
        anchors.verticalCenter: parent.verticalCenter
        Text{
            id: staticScore
            height: parent.height / 2
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Score :")
            font.pixelSize: font_size(parent.width, parent.height)
        }
        Item{
            id: voidItem2
            height: parent.height / 10
            anchors.top: staticScore.bottom
        }
        Text{
            anchors.top: voidItem2.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.score_count
            font.pixelSize: font_size(parent.width, parent.height)
        }
    }


}
