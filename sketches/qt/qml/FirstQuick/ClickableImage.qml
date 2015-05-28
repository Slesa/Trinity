import QtQuick 2.0

// Simple image which can be clicked

Image {
    id: root
    signal clicked

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}

