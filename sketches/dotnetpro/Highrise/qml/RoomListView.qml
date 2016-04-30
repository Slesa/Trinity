import QtQuick 2.3
import "components"

Rectangle {
    color: 'transparent'

    Rectangle {
        id: roomHeader
        /*width: 480;*/ height: 18
        color: 'transparent'
        //color: model.index % 2 == 0 ? "blue" : "black"
        anchors {
            left: parent.left
            right: scrollbar.left
            top: parent.top
        }
        Row {
            spacing: 10
            Text { width: buildingList.width-hlightCol.width-hstateCol.width-30; text: qsTr('Roomname'); color: 'white' }
            Text { id: hlightCol; width: 40; text: qsTr('Light'); color: 'white' }
            Text { id: hstateCol; width: 50; text: qsTr('Status'); color: 'white' }
        }
    }

    ListView {
        id: buildingList
        model: buildingModel
        focus: true
        clip: true
        delegate: roomDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        anchors {
            left: parent.left
            right: scrollbar.left
            top: roomHeader.bottom
            topMargin: 5
            bottom: parent.bottom
        }
    }
    ScrollBar {
        id: scrollbar
        flickable: buildingList
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }


    Component {
        id: roomDelegate
        Rectangle {
            /*width: 480;*/ height: 18
            color: 'green'
            //color: model.index % 2 == 0 ? "blue" : "black"
            Row {
                spacing: 10
                Text { width: buildingList.width-lightCol.width-stateCol.width-30; text: model.name; color: 'white' }
                Text { id: lightCol; width: 40; text: model.lightstate; color: 'white' }
                Text { id: stateCol; width: 50; text: model.roomstate; color: 'white' }
            }
         }
     }

}
