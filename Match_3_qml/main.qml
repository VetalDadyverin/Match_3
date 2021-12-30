import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Match_3_model_plugin 1.0


Window {
    id: root
    property int cell_size: 70
    property int click: 0
    property int first_index: -2
    readonly property int const_start : -2
    property int move_count: 0
    property int score_count : 0
    width: myGrid.ready ? cell_size * myGrid.listModel.get_columns() : 640
    height: myGrid.ready ? cell_size * myGrid.listModel.get_rows() * 1.12 : 640
    visible: true
    title: qsTr("Match 3")
    color: Qt.lighter("yellow")

    Item{
        id: quit
        anchors.fill: parent
        focus: true
        Keys.onPressed:
            function (event){
                //console.log(event.key)
                if(event.key === 81){
                    Qt.quit()
                }
            }
    }


    MyPopup{
        id: myPopup
    }

    InformRow{
        id: informRow
        width: parent.width
        height: (parent.height - myGrid.height) * 0.89
        anchors.top: parent.top
    }

    MyGrid{
        id: myGrid
        anchors.top: informRow.bottom
        onStopGame :{
            myPopup.open();
        }
    }
}
