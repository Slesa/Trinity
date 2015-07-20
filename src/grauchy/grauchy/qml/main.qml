import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
	id: root
	flags: Qt.FramelessWindowHint
    title: qsTr("Grauchy - the hotkey searcher")
    width: 800
    height: 600
    visible: true

	/* 
        Window frame with minimize, maximize and close
	*/
	Rectangle {
		id: windowBorder
		anchors.right: parent.right
		anchors.top: parent.top
		height: 24
		width: root.width
		color: '#362424'
	}

	Text {
		text: root.title
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCentr
	}

    MouseArea {
        height: 24
        width: parent.width
        anchors.fill: parent
        property variant clickPos: '1,1'

        onPressed: { clickPos = Qt.point(mouse.x, mouse.y) }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            root.x += delta.x
            root.y += delta.y
        }
    }
}
