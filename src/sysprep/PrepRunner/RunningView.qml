import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.StateMachine 1.12 as DSM

Control {

    GroupBox {
        id: progressView
        title: qsTr("Progress")
        height: 40
        anchors { margins: 5; left: parent.left; right: parent.right; top: parent.top }

        ProgressBar {
            value: 0.5
        }
    }

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
        anchors { margins: 5; left: parent.left; right: parent.right; top: progressView.bottom; bottom: logView.top }
        WaitForSshView {
            id: waitSshPage
            anchors.fill: parent
            visible: false
            //height: 100
            //width: 300
        }
    }

    GroupBox {
        id: logView
        title: qsTr("Output")
        height: 200
        anchors { margins: 5; left: parent.left; right: parent.right; bottom: buttonRow.top }
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
            enabled: runner.canQuit
            onClicked: Qt.quit()
        }
        Button {
            text: qsTr("&Back")
            height: parent.height
            enabled: runner.canBack
            onClicked: runner.stopRunner()
        }
        Button {
            text: qsTr("Co&ntinue")
            height: parent.height
            enabled: runner.canContinue
            onClicked: runner.continueRunner()
        }
    }

    DSM.StateMachine {
        initialState: runningState
        running: true
        DSM.State {
            id: runningState
            DSM.SignalTransition {
                targetState: waitSshState
                signal: runner.waitForSsh
            }
            onEntered: {
                console.log("runningState entered")
            }
            onExited: {
                console.log("runningState exited")
            }
        }
        DSM.State {
            id: waitSshState
            DSM.SignalTransition {
                targetState: runningState
                signal: runner.continueRun
            }
            onEntered: {
                waitSshPage.Visible = true
                console.log("waitSshState entered")
            }
            onExited: {
                waitSshPage.Visible = false
                console.log("waitSshState exited")
            }
        }
    }
}
