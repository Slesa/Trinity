import QtQuick 2.3
import QtGraphicalEffects 1.0
import "components"

FocusScope {
    id: root

    GridView {
        id: roomList
        model: roomsModel
        cellWidth: root.width/2-20
        cellHeight: model.count > 0 ? root.height / (model.count * 2) : 0
        focus: true
        clip: true
        delegate: roomDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        anchors {
            left: parent.left
            right: scrollbar.left
            top: parent.top
            topMargin: 5
            bottom: parent.bottom
        }
    }
    ScrollBar {
        id: scrollbar
        flickable: roomList
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }


    Component {
        id: roomDelegate

        Rectangle {
            anchors.margins: 10
            width: roomList.cellWidth-10; height: roomList.cellHeight-10
            color: model.roomstate===0 ? '#A16752' : 'transparent'
            clip: true

            RadialGradient {
                id: lightbulb
                horizontalRadius: parent.width/2; verticalRadius: 40
                width: parent.width/2
                height: parent.height
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#88AAAA33" }
                    GradientStop { position: 0.5; color: "transparent" }
                }
                anchors {
                    top: parent.top
                    topMargin: -lightbulb.height/2
                    horizontalCenter: parent.horizontalCenter
                }
                visible: model.lightstate===1
            }

            Text {
                text: model.name; color: 'white'; font.pointSize: 16
                opacity: 0.2
                anchors.centerIn: parent
            }
         }
    }
}
