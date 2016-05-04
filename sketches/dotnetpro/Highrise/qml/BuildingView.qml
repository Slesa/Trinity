import QtQuick 2.3
import QtQuick.Controls 1.2
import "components"

Rectangle {
    color: 'transparent'
    Row {
        id: inputLine
        height: 20
        spacing: 5
        anchors {
            left: parent.left
            leftMargin: 20
            right: parent.right
            top: parent.top
            topMargin: 20
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
        }
        EditBox {
            id: editFilter
            anchors.verticalCenter: parent.verticalCenter
            width: 160
            //text: buildingProxy.filterRegExp
            //hint: qsTr('Filter')
            onInputChanged: {
                console.debug("Text changed");
                buildingProxy.setFilterRegExp(text);
            }
        }
        IconButton {
            anchors.verticalCenter: parent.verticalCenter
            icon: 'qrc:/assets/clear.png'
            text: qsTr('Reset filter')
            onClicked: {
                console.debug("Clear filter");
                editFilter.text = '';
            }
        }
    }

    RoomListView {
        id: roomList
        anchors {
            left: parent.left
            margins: 20
            right: parent.right
            top: inputLine.bottom
            bottom: parent.bottom
        }
    }
}
