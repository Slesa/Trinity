import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent

    Frame {
        background: Rectangle {
            color: "transparent"
            border.color: "#21be2b"
            radius: 2
        }
        Column {
            id: topLabel
            Text { text: qsTr("Running on:") }
            Text { text: sysinfo.osName }
            Text { text: qsTr("Operating system:") }
            Text { text: sysinfo.kernelType }
            Text { text: qsTr("Distribution:") }
            Text { text: sysinfo.distribution }
            Text { text: qsTr("Window manager:") }
            Text { text: sysinfo.wmName }
        }
/*
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
        value: model.currentStep
    } */
    }
}
