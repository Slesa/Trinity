import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.Center: parent.Center

    Column {
        Row {
            TextField { readOnly: true; text: qsTr("Running on:") }
            TextField { readOnly: true; text: systeminfo.osName }
        }
        Row {
            TextField { readOnly: true; text: qsTr("Operating system:") }
            TextField { readOnly: true; text: systeminfo.kernelType }
        }
        Row {
            TextField { readOnly: true; text: qsTr("Distribution:") }
            TextField { readOnly: true; text: systeminfo.distribution }
        }
        Row {
            TextField { readOnly: true; text: qsTr("Window manager:") }
            TextField { readOnly: true; text: systeminfo.wmName }
        }
    }
}
