import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQml.StateMachine 1.12 as DSM

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Preparation Runner")

    StartView {
        anchors.fill: parent
        id: startPage
    }

    Control {
        id: runningView
        anchors.fill: parent
        visible: false

        WaitForSshView {
            anchors.fill: parent
            id: waitSshPage
            visible: false
        }

        ListView {
            id: logView
            model: runner.logfile
            height: 200
            anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
            delegate: Rectangle {
                border.color: "lightblue"
                height: 25
                //width: parent.width
                Text {
                    anchors.centerIn: parent
                    text: modelData
                }
            }
        }
    }

    DSM.StateMachine {
        initialState: startState
        running: true
        DSM.State {
            id: startState
            DSM.SignalTransition {
                targetState: runningState
                signal: runner.running
            }
            onEntered: console.log("startState entered")
            onExited: {
                startPage.visible = false
                console.log("startState exited")
            }
        }

        DSM.State {
            id: runningState
            DSM.SignalTransition {
                targetState: waitSshState
                signal: runner.waitForSsh
            }
            onEntered: console.log("runningState entered")
            onExited: {
                runningView.visible = true
                console.log("runningState exited")
            }
        }

        DSM.State {
            id: waitSshState
            /* DSM.SignalTransition {
                targetState: s2
                signal: runner.waitForOk
            } */
            onEntered: {
                waitSshPage.visible = true
                // runner.continueRunner()
                console.log("waitSshState entered")
            }
            onExited: {
                waitSshPage.visible = false
                console.log("waitSshState exited")
            }
        }
    }

}
