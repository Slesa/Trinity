import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent

    //Column {
    //    anchors.fill: parent

        Frame {
            id: topLabel

            anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 20 }
            background: Rectangle {
                color: "transparent"
                border.color: "#21be2b"
                radius: 2
            }
            Text {
                text: qsTr("Detecting OS")
            }
        }

    Frame {
        anchors { horizontalCenter: parent.horizontalCenter; bottom: topLabel.bottom; bottomMargin: 20 }
        background: Rectangle {
            color: "transparent"
            border.color: "#21be2b"
            radius: 2
        }
        Text {
            text: qsTr("Probing:")
        }
        Text {
            text: model.currentOs
        }
    }

    ProgressBar {
        anchors { horizontalCenter: parent.horizontalCenter; verticalCenterOffset: parent.verticalCenter }
        value: model.currentStep
    }
    //}
}
