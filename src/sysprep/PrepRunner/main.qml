import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Preparation Runner")

    CustomizeView {
        anchors { top: parent.top; bottom: buttonRow.top; left: parent.left; right: infoRow.left; rightMargin: 10 }
    }
    SystemInfoView {
        id: infoRow
        anchors { top: parent.top; bottom: buttonRow.top; right: parent.right }
    }

    ButtonView {
        id: buttonRow
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; right: parent.right }
    }
    /* ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    } */
}
