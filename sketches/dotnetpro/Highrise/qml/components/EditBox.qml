import QtQuick 2.4

FocusScope {
    id: focusScope
    width: 250; height: 32

    property alias text: input.text

    signal inputChanged

    Rectangle {
        anchors.fill: parent
        color: '#FF5198d0'

        Image {
            id: watermark
            anchors {
                //fill: parent
                leftMargin: 8
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/assets/magnifier.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: { focusScope.focus = true }
        }

        TextInput {
            id: input
            anchors { left: parent.left; leftMargin: 8; right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
            color: 'white'
            focus: true
            selectByMouse: true
            onTextChanged: {
                focusScope.inputChanged();
            }
        }

        states: State {
            name: "hasText"; when: focusScope.activeFocus // input.text != ''
            PropertyChanges { target: watermark; opacity: 0 }
        }

        transitions: [
            Transition {
                from: ""; to: "hasText"
                NumberAnimation { exclude: watermark; properties: "opacity" }
            },
            Transition {
                from: "hasText"; to: ""
                NumberAnimation { properties: "opacity" }
            }
        ]
    }
}

