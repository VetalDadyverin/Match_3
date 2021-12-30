import QtQuick 2.0
import Match_3_model_plugin 1.0

Rectangle{
    property alias grid: _grid
    property alias listModel: _listModel
    property bool ready: false
    signal stopGame()
    anchors.horizontalCenter: parent.horizontalCenter
    border.color: "black"
    border.width: 2
    color: Qt.lighter("yellow")
    width: root.width * 0.95
    height: root.height * 0.8485
    radius: 10

    function startFalling(){
        if(first_index === const_start){
            if(listModel.start_falling()){
                if(myGrid.listModel.stop_game()){
                    stopGame();
                }
            }
        }
        else{
            listModel.falling_down();
            first_index = const_start;
        }
        score_count = listModel.get_score();
    }

    GridView{
        id: _grid
        width: parent.width
        height: parent.height
        anchors.fill: parent
        cellWidth: parent.width / _listModel.get_columns()
        cellHeight: cellWidth
        interactive: false
        model: _listModel
        delegate: MyComponent{}
        move: gridMoveTrans
        displaced: gridMoveTrans
        add: gridInsertTrans
        Component.onCompleted: ready = true
        Transition {
            id: gridMoveTrans
            NumberAnimation{
                properties: "x, y"
                duration: 400
            }
            onRunningChanged: {
                if(!running){
                    startFalling()
                }
            }
        }
        Transition {
            id: gridInsertTrans
            NumberAnimation{
                properties: "y"
                duration: 400
                from: -100
            }
            onRunningChanged: {
                if(!running){
                    startFalling()
                }
            }
        }
    }

    MyListModel {
        id: _listModel
    }

}
