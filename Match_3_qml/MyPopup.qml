import QtQuick 2.0
import QtQuick.Controls 2.15

Popup {
    id: popup
    anchors.centerIn: parent
    width: root.width / 1.5
    height: width / 2.5
    z:1
    modal: true
    closePolicy: Popup.NoAutoClose
    background :Rectangle{
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.lighter("orange")}
            GradientStop { position: 1.0; color: "orange"}
        }
        border.color: "black"
        radius: 5
    }

    Text{
        id: popup_text
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Yeah, You have won!!!"
        font.bold: true
        font.pixelSize: parent.width / 12
        //font.italic: true
    }

    Button{
        id: restart_button
        width: parent.height
        height: width / 2.6
        anchors.topMargin: height / 1.5
        anchors.top: popup_text.bottom
        anchors.left: parent.left
        text: "Restart"
        background :Rectangle{
            gradient: Gradient {
                GradientStop { position: 0.0; color: restart_button.pressed ? Qt.lighter("#FFAC1C"): Qt.lighter("yellow")}
                GradientStop { position: 1.0; color: restart_button.pressed ? "#FFAC1C" : Qt.darker("yellow")}
            }
            border.color: "black"
            radius: 5
        }
        onClicked: {
            myGrid.listModel.start_shuffle();
            popup.close();
            root.score_count = 0;
            root.move_count = 0;
            quit.focus = true;
        }
    }

    Button{
        id: quit_button
        width: parent.height
        height: width / 2.6
        anchors.topMargin: height / 1.5
        anchors.top: popup_text.bottom
        anchors.right: parent.right
        text: "Quit"
        background :Rectangle{
            gradient: Gradient {
                GradientStop { position: 0.0; color: quit_button.pressed ? Qt.lighter("#FFAC1C") : Qt.lighter("yellow")}
                GradientStop { position: 1.0; color: quit_button.pressed ? "#FFAC1C" : Qt.darker("yellow")}
            }
            border.color: "black"
            radius: 5
        }
        onClicked: {
            Qt.quit()
        }
    }
}
