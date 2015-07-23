import QtQuick 2.4

Rectangle {
    id: root
    width: 100
    height: 62
    color: 'transparent'

    property int buttonWidth: 80
    property int buttonHeight: 80

    ButtonIconText {
        id: buttonOptions
        text: qsTr('Options')
        icon: '../assets/options.png'
        anchors {
            left: parent.left
            leftMargin: 5
            right: parent.right
            rightMargin: 5
//            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 5
        }
        width: buttonWidth
        height: buttonHeight
    }

    ButtonIconText {
        id: buttonQuit
        text: qsTr('Quit')
        icon: '../assets/quit.png'
        anchors {
            left: parent.left
            leftMargin: 5
            right: parent.right
            rightMargin: 5
//            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 5
        }
        width: buttonWidth
        height: buttonHeight
    }

    Component.onCompleted: {
        buttonQuit.onClicked.connect(Qt.quit)
    }
}

