import QtQuick 2.0

Rectangle {
    id: root

    width: 320; height: 480

    onHeightChanged: console.log('height:', height)

    border.color: "lightsteelblue"
    border.width: 4
    radius: 8

    gradient: Gradient {
        GradientStop { position: 0; color: "#ffffff" }
        GradientStop { position: 0.5; color: "lightsteelblue" }
        GradientStop { position: 1.0; color: "slategray" }
    }

//    color: "#D8D8D8"

    Transformer {
        id: rocket
        x: 10
//        x: (parent.width-width)/2; y: 40
//        source: 'rocket.png'
/*        MouseArea {
            id: area
            width: parent.width
            height: parent.height
            onClicked: label.visible = !label.visible
        }*/
    }

    Text {
        id: label
        y: rocket.y + rocket.height + 20
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        text: 'Rocket'

    }
    Text {
        id: timer
        y: root.height - 30

        width: root.width
        color: "black"


        horizontalAlignment: Text.AlignHCenter
        text: "Times: " + root.times
        font.family: "Courier New"
        font.pixelSize: 28
        elide: Text.ElideMiddle
//        style: Text.Sunken
//        styleColor: "#FF4444"
    }

    Button {
        id: button
        x: 12; y: 12
        text: "Start"
        onClicked: {
            timer.text = "waiting..."
        }
    }

    focus: true

    property int times: 0

    Keys.onSpacePressed: {
        increment()
    }

    Keys.onEscapePressed: {
        timer.text = ''
    }

    function increment() {
        times = times + 1
    }
}

//qmlscene ~/work/github/Trinity/sketches/qt/qml/test.qml
