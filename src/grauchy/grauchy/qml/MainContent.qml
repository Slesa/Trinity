import QtQuick 2.4

Rectangle {
    id: root
    width: 100
    height: 200
    color: 'darkgray'

    AreaButtons {
        id: areaButtons
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 100
    }

    AreaContent {
        id: areaContent
        anchors.right: areaButtons.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
}

