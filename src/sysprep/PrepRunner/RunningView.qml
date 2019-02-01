import QtQuick 2.12
import QtQuick.Controls 2.5

Control {
/*
    Rectangle {
        id: waitSshPage
        color: "blue"
        opacity: 0.3
        height: 100
        //anchors.fill: parent
        anchors { top: parent.top; left: parent.left; leftMargin: 5; right: parent.right; rightMargin: 5 }
    }
*/

    GroupBox {
        id: runContent
        anchors { margins: 5; left: parent.left; right: parent.right; top: parent.top; bottom: logView.top }
        WaitForSshView {
            anchors.fill: parent
            id: waitSshPage
            //visible: false
            //height: 100
            //width: 300
        }
    }

    GroupBox {
        id: logView
        title: qsTr("Output")
        height: 200
        anchors { left: parent.left; leftMargin: 5; right: parent.right; rightMargin: 5; bottom: buttonRow.top }
        // color: "white"
        ListView {
            model: logger.logfile
            anchors.fill: parent
            //height: 200
            delegate: Rectangle {
                //border.color: "lightblue"
                height: 22
                width: parent.width
                Text {
                    // anchors.centerIn: parent
                    text: modelData
                }
            }
        }
    }

    Row {
        id: buttonRow
        height: 35
        spacing: 5
        padding: 5
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; right: parent.right }
        Button {
            text: qsTr("&Close")
            height: parent.height
            onClicked: Qt.quit()
        }
        Button {
            text: qsTr("&Back")
            height: parent.height
            visible: runner.canBack
            onClicked: runner.stopRunner()
        }
        Button {
            text: qsTr("Co&ntinue")
            height: parent.height
            visible: runner.canContinue
            onClicked: runner.continueRunner()
        }
    }
}
