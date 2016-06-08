import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle {
    id: root

    property alias icon: icon.source
    property alias text: label.text
    property alias font: label.font

    signal clicked

    width: icon.width + label.contentWidth + 20
    height: parent.height
    antialiasing: true
    color: 'transparent'
    border.color: mouseArea.containsMouse || focus ? 'white' : 'transparent'

    Keys.onSpacePressed: {
        root.clicked();
    }

//    anchors.verticalCenter: parent.verticalCenter
//    color: mouseArea.containsMouse ? '#e3f6fc' : 'white'
//    border.color: mouseArea.containsMouse ? '#01adef' : 'white'

    MouseArea {
        id: mouseArea
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: icon.width + label.width + 20
        hoverEnabled: true
        onPressed: {
            root.clicked();
        }

        Image {
            id: icon
//            source: mouseArea.containsMouse ? root.iconHover : root.iconNormal
            clip: true
            width: 24
            height: 24
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: label
            color: 'white'
            anchors.left: icon.right
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

