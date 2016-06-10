import QtQuick 2.3
import "components"

FocusScope {

    Rectangle {
        id: roomHeader
        height: 18
        color: 'transparent'
        anchors {
            left: parent.left
            right: scrollbar.left
            top: parent.top
        }
        Row {
            spacing: 10
            Text { width: buildingList.width-hlightCol.width-hstateCol.width-30; text: qsTr('Roomname'); color: 'white'; font.pointSize: 14 }
            Text { id: hlightCol; width: 40; text: qsTr('Light'); color: 'white'; font.pointSize: 14 }
            Text { id: hstateCol; width: 50; text: qsTr('Status'); color: 'white'; font.pointSize: 14 }
        }
    }

    ListView {
        id: buildingList
        model: buildingProxy
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
            width: parent.width; height: 22
            color: mouseArea.containsMouse ? 'lightsteelblue' : 'transparent'
            opacity: mouseArea.containsMouse ? 0.2 : 1.0
            //color: model.index % 2 == 0 ? "blue" : "black"
            Row {
                spacing: 10
                Text { width: buildingList.width-lightCol.width-stateCol.width-30; text: model.name; color: 'white'; font.pointSize: 16 }
                Text { id: lightCol; width: 40; text: getLightStateText(model.lightstate); color: 'white'; font.pointSize: 16 }
                Text { id: stateCol; width: 50; text: getRoomStateText(model.roomstate); color: 'white'; font.pointSize: 16 }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onDoubleClicked: {
                    model.lightstate = model.lightstate===1 ? 0 : 1;
                }

            }
            Keys.onReturnPressed: {
                model.lightstate = model.lightstate===1 ? 0 : 1;
            }
        }
    }

    function getLightStateText(state) {
        return state===1 ? qsTr('On') : qsTr('Off');
    }
    function getRoomStateText(state) {
        return state===0 ? qsTr('Ok') : qsTr('Error');
    }
}
