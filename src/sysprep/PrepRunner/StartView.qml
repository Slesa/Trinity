import QtQuick 2.0
import QtQuick.Controls 2.2

Control {
    CustomizeView {
        anchors { top: parent.top; bottom: buttonRow.top; left: parent.left; leftMargin: 5; right: infoRow.left; rightMargin: 10 }
    }
    SystemInfoView {
        id: infoRow
        anchors { top: parent.top; bottom: buttonRow.top; right: parent.right; rightMargin: 5 }
    }

    ButtonView {
        id: buttonRow
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; right: parent.right }
    }
}
