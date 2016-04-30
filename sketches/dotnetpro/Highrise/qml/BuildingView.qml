import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    color: 'transparent'
    Row {
        id: inputLine
        height: 20
        spacing: 5
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr('Filter:')
        }
        TextInput {
            anchors.verticalCenter: parent.verticalCenter
            width: 160
        }
        Button {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr('Reset filter')
        }
    }

    RoomListView {
        id: roomList
        anchors {
            left: parent.left
            right: parent.right
            top: inputLine.bottom
            bottom: parent.bottom
        }
    }
}
