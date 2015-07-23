import QtQuick 2.4

Rectangle {
    id: root
    width: 100
    height: 62
    color: 'blue'

    ButtonIconText {
        text: qsTr('Options')
        icon: '../assets/options.png'
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

