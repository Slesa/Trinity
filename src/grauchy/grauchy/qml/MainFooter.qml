import QtQuick 2.0

Rectangle {
    id: root
    color: 'gray'
    width: 100
    height: 62
    property alias textColor: textMsg.color

    Text {
        id: textMsg
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: 'Status'
    }
}

