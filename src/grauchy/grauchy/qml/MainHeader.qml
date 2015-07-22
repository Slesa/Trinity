import QtQuick 2.0

Rectangle {
    id: root

    signal moveWindow
    property double winx: 0
    property double winy: 0
    property alias title: textTitle.text
    property alias textColor: textTitle.color

    Text {
        id: textTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        color: 'gray'
        width: 1
        anchors.bottom: root.bottom
    }


    MouseArea {
        height: 24
        width: parent.width
        anchors.fill: parent
        property variant clickPos: '1,1'

        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            winx += delta.x
            winy += delta.y
            root.moveWindow()
        }
    }
}

