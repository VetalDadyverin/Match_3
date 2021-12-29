import QtQuick 2.0

Item {
    id: itemDelegate
    width: grid.cellWidth
    height: grid.cellHeight
    visible: !model.remove
    Rectangle{
        id: componentRect
        width: grid.cellWidth * 0.93
        height: width
        border.color: "black"

        gradient: Gradient {
            GradientStop { position: 0.0; color: model.color === "black" ? Qt.darker("darkgrey") : model.color }
            GradientStop { position: 1.0; color: model.color === "black" ? "black" : Qt.darker(Qt.darker(model.color))}
        }
        radius: 50
        anchors.centerIn: parent
        scale: index === root.first_index ? 0.75 : 1
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(root.click === 0){
                    root.click = 1;
                    root.first_index = index;
                }
                else{
                    root.click = 0;
                    if(myGrid.listModel.try_to_swap(root.first_index, index)){
                        root.move_count++;
                    }
                    root.first_index = -1;
                }
                quit.focus = true
            }
        }

        Behavior on scale {
            NumberAnimation  {
                duration: 400
            }
        }

    }
}
