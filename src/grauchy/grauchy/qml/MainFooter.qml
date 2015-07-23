import QtQuick 2.4

Rectangle {
    id: root
    color: 'gray'
    width: 100
    height: 62
    property alias textColor: textMsg.color

    Text {
        id: textMsg
        text: 'Status'
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
    }
}

