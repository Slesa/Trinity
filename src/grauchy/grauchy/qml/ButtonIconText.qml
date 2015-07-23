import QtQuick 2.4
import QtQuick.Controls 1.2

Rectangle {
    id: root

    property alias text: label.text
    property alias icon: icon.source
    property string highIcon: ''
    property string normColor: 'white'
    property string highColor: '#26c79c'

    signal onClicked

    color: 'transparent'
    width: 100
    height: 100

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onPressed: {
            root.onClicked();
        }

        Image {
            id: icon
            width: 32
            height: 32
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
            color: mouseArea.containsMouse ? root.highColor : root.normColor
            font.pixelSize: 24
            anchors {
                bottom: bottomFrame.top
                bottomMargin: -1
                horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: bottomFrame
            height: 2
            color: mouseArea.containsMouse ? root.highColor : 'transparent'
            anchors {
                bottom: parent.bottom
//                bottomMargin:-5
                left: label.left
                right: label.right
            }
        }
    }
}

