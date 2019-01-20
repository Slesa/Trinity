import QtQuick 2.12
import QtQuick.Controls 2.5

Row {
    height: 35
    spacing: 5
    padding: 5
    Button {
        text: qsTr("&Close")
        height: parent.height
        onClicked: Qt.quit()
    }
    Button {
        text: qsTr("&Start")
        height: parent.height
        onClicked: runner.startRunner()
    }
}
