import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    color: 'transparent'
    Row {
        spacing: 5
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr('Filter:')
        }
        TextInput {
            anchors.verticalCenter: parent.verticalCenter
            width: 160
        }
        Button {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr('Reset filter')
        }
    }
}
