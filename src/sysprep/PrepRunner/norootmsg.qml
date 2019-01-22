import QtQuick 2.2
import QtQuick.Dialogs 1.1

MessageDialog {
    id: messageDialog
    title: qsTr("Preparation Runner - No root rights")
    text: qsTr("Application has no root rights and cannot access system data.\n
           Please re-run as root / Administrator")
    onAccepted: {
        console.log("And of course you could only agree.")
        Qt.quit()
    }
    Component.onCompleted: visible = true
}
