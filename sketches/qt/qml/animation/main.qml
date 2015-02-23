import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    color: "#343434"
    visible: true


    Rectangle {
        id: page


        Image {
            id: icon
            x: 10
            y: 20
            width: 64
            height: 64
            source: "earth.png"
        }

        Rectangle {
            id: topLeftRect
            width: 64
            height: 64
            color: "#00000000"
            radius: 6
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 20
            border.color: "#808080"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    page.state = ''
                }

                x: 0
                y: 0
                width: 64
                height: 64
            }
        }

        Rectangle {
            id: middleRightRect
            x: 0
            y: 0
            width: 64
            height: 64
            color: "#00000000"
            radius: 6
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            border.color: "#808080"
            MouseArea {
                id: mouseArea1
                x: 0
                y: 0
                width: 64
                height: 64
                anchors.fill: parent
                onClicked: {
                    page.state = 'State1'
                }
            }
        }

        Rectangle {
            id: bottomLeftRect
            x: 0
            y: 0
            width: 64
            height: 64
            color: "#00000000"
            radius: 6
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            border.color: "#808080"
            MouseArea {
                id: mouseArea2
                x: 0
                y: 0
                width: 64
                height: 64
                anchors.fill: parent
                onClicked: {
                    page.state = 'State2'
                }
            }
        }

        states: [
            State {
                name: "State1"

                PropertyChanges {
                    target: icon
                    x: middleRightRect.x
                    y: middleRightRect.y
                }
            },

            State {
                name: "State2"

                PropertyChanges {
                    target: icon
                    x: bottomLeftRect.x
                    y: bottomLeftRect.y
                }
            }
        ]
    }

}
