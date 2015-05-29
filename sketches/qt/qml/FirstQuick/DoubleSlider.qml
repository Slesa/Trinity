import QtQuick 2.0

Rectangle {
    id: root
    width: 300; height: 28
    anchors.centerIn: parent

    property int lowerValue: Math.round(lower.x*100/root.width)
    property int upperValue: Math.round(upper.x*100/root.width)

    color: "slategray"

    Rectangle {
        id: lower
        y: (root.height - lower.height)/2
        width: 40; height: 40;
        radius: 33
        color: "green"
        MouseArea {
            anchors.fill: parent
            drag.target: parent; drag.axis: "XAxis"
            drag.minimumX: 0; drag.maximumX: upper.x - lower.width
        }
    }

    Rectangle {
       id: upper
       x: root.width - upper.width
       y: (root.height - upper.height)/2
        width: 40; height: 40
        radius: 33
        color: "red"
        MouseArea {
            anchors.fill: parent
            drag.target: parent; drag.axis: "XAxis"
            drag.minimumX: lower.x + lower.width; drag.maximumX: root.width - upper.width
        }
    }
}

