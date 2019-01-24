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
        Rectangle {
            color: "orange"
            opacity: 0.3
            anchors.fill: parent
        }
    }

    Control {
        id: runningView
        anchors.fill: parent
        visible: false
/*
        Rectangle {
            color: "blue"
            opacity: 0.3
            anchors.fill: parent
        }
*/
/*
        WaitForSshView {
            // anchors.fill: parent
            id: waitSshPage
            visible: false
            height: 300
            width: 300
            //anchors { left: parent.left; leftMargin: 5; right: parent.right; rightMargin: 5; top: parent.top }
        }
*/
        ListView {
            id: logView
            model: runner.logfile
            anchors.fill: parent
            //height: 200
//            anchors { top: parent.bottom; left: parent.left; leftMargin: 5; right: parent.right; rightMargin: 5; bottom: parent.bottom }
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
            onEntered: {
                runningView.visible = true
                console.log("runningState entered")
            }
            onExited: {
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
