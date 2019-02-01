import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    //anchors.fill: parent.fill
    color: "lightblue"
    Column {
        anchors.fill: parent
        anchors.margins: 5

        Text {
            // anchors { top: parent.top; left: parent.left; right: parent.right }
            font.pointSize:12
            wrapMode: Text.WordWrap
            text: qsTr("Please add SSH keys to GitHub and GitLab and press then Continue")
        }
    }
}
