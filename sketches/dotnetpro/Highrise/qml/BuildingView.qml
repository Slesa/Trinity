import QtQuick 2.3
import QtQuick.Controls 1.2
import "components"

Rectangle {
    id: root
    color: 'transparent'

    BuildingViewHeader {
        id: header
        activeFocusOnTab: true
        onFocusChanged: {
            if(focus===false)
                roomList.forceActiveFocus();
        }
    }

    RoomListView {
        id: roomList
        width: root.width/2
        focus: true
        activeFocusOnTab: true
        anchors {
            margins: 20
            left: parent.left
            top: header.bottom
            bottom: parent.bottom
        }
    }

    RoomGridView {
        id: roomGrid
        activeFocusOnTab: true
        anchors {
            margins: 20
            top: header.bottom
            bottom: parent.bottom
            left: roomList.right
            right: parent.right
        }
    }
}
