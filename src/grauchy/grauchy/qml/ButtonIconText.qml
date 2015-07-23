import QtQuick 2.4
import QtQuick.Controls 1.2

Rectangle {
    id: root

    property alias text: label.text
    property alias icon: icon.source
    color: 'red'

    signal onClicked

    width: 100
    height: 62

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onPressed: {
            root.onClicked();
        }

        Image {
            id: icon
            sourceSize: Qt.size(32,32)
            smooth: true
            anchors {
                bottom: label.top
                bottomMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
        }

        Text {
            id: label
            text: 'Text'
            color: 'white'
            font.pixelSize: 24
            anchors {
                bottom: bottomFrame.top
                bottomMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: bottomFrame
            width: 1
            color: 'white'
            anchors {
                bottom: parent.bottom
                bottomMargin: 5
                left: parent.left
                right: parent.right
            }
        }
    }
}

