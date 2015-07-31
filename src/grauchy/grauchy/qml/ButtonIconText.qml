import QtQuick 2.4
import QtQuick.Controls 1.2

// http://doc.qt.io/qt-5/qtsensors-qmlsensorgestures-button-qml.html
Item {
    id: button
    property alias text: label.text
    property color color: 'white'
    property color hoverColor: '#26c79c'
    property color pressColor: '#26c79c'
    property alias icon: icon.source
    property string hoverIcon: ''
    property string pressIcon: ''
    property int fontSize: 24
//    property int borderWidth: 1
//    property int borderRadius: 2
    width: 60
    height: 30
//    scale: state=='Pressed' ? 0.96 : 1.0
    onEnabledChanged: state = ''
    signal clicked
/*
    Behavior on scale {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }
*/
    Rectangle {
        id: root
        anchors.fill: parent
//        radius: borderRadius
        color: 'transparent'
//        color: button.enabled ? button.color : 'grey'
//        border.width: borderWidth
//        border.color: 'black'

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
            color: button.color
            text: 'Text'
            font.pointSize: fontSize
            anchors {
                bottom: bottomFrame.top
                bottomMargin: -1
                horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: bottomFrame
            height: 2
            color: 'transparent'
            anchors {
                bottom: parent.bottom
//                bottomMargin:-5
                left: label.left
                right: label.right
            }
        }
    }

    states: [
        State {
            name: 'Hovering'
            PropertyChanges {
                target: label
                color: hoverColor
            }
            PropertyChanges {
                target: bottomFrame
                color: hoverColor
            }
        },
        State {
            name: 'Pressed'
            PropertyChanges {
                target: label
                color: hoverColor
            }
            PropertyChanges {
                target: bottomFrame
                color: hoverColor
            }
            PropertyChanges {
                target: bottomFrame
                height: 4
            }
        }
    ]

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: { button.state = 'Hovering' }
        onExited: { button.state = '' }
        onClicked: { button.clicked(); }
        onPressed: { button.state = 'Pressed' }
        onReleased: {
            if (containsMouse)
                button.state = 'Hovering';
            else
                button.state = '';
        }
    }
}
