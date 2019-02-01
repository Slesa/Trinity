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
        id: startPage
        anchors.fill: parent
        /* Rectangle {
            color: "white"
            opacity: 0.3
            anchors.fill: parent
        } */
    }

    RunningView {
        id: runningPage
        anchors.fill: parent
        visible: false
        /* Rectangle {
            color: "yellow"
            opacity: 0.3
            anchors.fill: parent
        } */
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
            onEntered: {
                startPage.visible = true
                console.log("startState entered")
            }
            onExited: {
                startPage.visible = false
                console.log("startState exited")
            }
        }

        DSM.State {
            id: runningState
            DSM.SignalTransition {
                targetState: startState
                signal: runner.runStopped
            }
            onEntered: {
                runningPage.visible = true
                console.log("runningState entered")
            }
            onExited: {
                runningPage.visible = false
                console.log("runningState exited")
            }
        }
/*
        DSM.State {
            id: waitSshState
            /* DSM.SignalTransition {
                targetState: s2
                signal: runner.waitForOk
            } * /
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
*/
    }
}
