import QtQuick 2.3
import "components"

Rectangle {
    id: root
    color: 'transparent'


    GridView {
        id: roomList
        model: roomsModel
        cellWidth: root.width/2-20
        cellHeight: model.count > 0 ? (root.height-10) / model.count : 0
        focus: true
        clip: true
        delegate: roomDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        anchors {
            left: parent.left
            right: scrollbar.left
            top: parent.top
            topMargin: 5
            bottom: parent.bottom
        }
    }
    ScrollBar {
        id: scrollbar
        flickable: roomList
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }


    Component {
        id: roomDelegate
        Rectangle {
            // /*width: 480;*/ height: 18
            color: model.roomstate!==0 ? 'red' : 'green'
            //color: model.index % 2 == 0 ? "blue" : "black"
            Text { text: model.name; color: 'grey'; font.pointSize: 16 }
            Text { id: lightCol; width: 40; text: model.lightstate; color: 'white'; font.pointSize: 16 }
            Text { id: stateCol; width: 50; text: model.roomstate; color: 'white'; font.pointSize: 16 }
         }
     }

}
