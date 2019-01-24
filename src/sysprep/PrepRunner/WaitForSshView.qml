import QtQuick 2.0
import QtQuick.Controls 2.2

Column {
    anchors.fill: parent

    TextField {
        // anchors { top: parent.top; left: parent.left; right: parent.right }
        text: qsTr("Please add SSH keys to GitHub and GitLab and press then Continue")
    }

    Button {
        // anchors { bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right }
        text: qsTr("Continue")
    }
}
