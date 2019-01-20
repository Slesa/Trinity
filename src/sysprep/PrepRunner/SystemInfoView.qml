import QtQuick 2.12
import QtQuick.Controls 2.2

GroupBox {
    title: qsTr("System")

    Column {
        spacing: 5
        padding: 5
        Column {
            Label { text: qsTr("Running on:") }
            TextInput { readOnly: true; text: systeminfo.osName; color: "white" }
        }
        Column {
            Label { text: qsTr("Operating system:") }
            TextInput { readOnly: true; text: systeminfo.kernelType; color: "white" }
        }
        Column {
            Label { text: qsTr("Distribution:") }
            TextInput { readOnly: true; text: systeminfo.distribution; color: "white" }
        }
        Column {
            Label { text: qsTr("Window manager:") }
            TextInput { readOnly: true; text: systeminfo.wmName; color: "white" }
        }
    }
}
