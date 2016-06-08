import QtQuick 2.4

FocusScope {
    id: focusScope
    width: 250; height: 32

    property alias text: input.text
    signal inputChanged

    Rectangle {
        id: root
        width: 250; height: 32
        //anchors.fill: parent
        color: '#FF5198d0'

        MouseArea {
            anchors.fill: parent
            onClicked: { focusScope.focus = true; }
        }
        Keys.onEscapePressed: { focusScope.focus = false; }

        Image {
            id: watermark
            anchors {
                //fill: parent
                leftMargin: 8
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/assets/magnifier.png"
        }

        TextInput {
            id: input
            anchors { left: watermark.right; leftMargin: 8; right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
            color: 'white'
            //selectByMouse: true
            onTextChanged: {
                focusScope.inputChanged();
            }
        }

        states: State {
            name: "hasText"; when: input.text != ''
            PropertyChanges { target: watermark; opacity: 0; width: 0 }
        }

        transitions: [
            Transition {
                ParallelAnimation {
                //from: ""; to: "hasText"
                NumberAnimation { properties: "width"; duration: 500 }
                OpacityAnimator { target: watermark; duration: 300 }
                }
            } /*,
            Transition {
                from: "hasText"; to: ""
                NumberAnimation { properties: "opacity, width" }
            }*/
        ]
    }
}

