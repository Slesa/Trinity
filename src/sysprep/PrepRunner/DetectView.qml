import QtQuick 2.0
import QtQuick.Controls 2.2

Item {

    Column {
    Frame {
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
    }
    }
}
