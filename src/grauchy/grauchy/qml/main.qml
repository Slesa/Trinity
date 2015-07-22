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
    color: '#262626'

	/* 
        Window frame with minimize, maximize and close
	*/
    MainHeader {
        id: windowTitle
        anchors.left: parent.left
        anchors.right: parent.right
		anchors.top: parent.top
		height: 24
        title: root.title
        winx: root.x
        winy: root.y
        color: root.color
        textColor: 'white'

        onMoveWindow: {
            root.x = windowTitle.winx
            root.y = windowTitle.winy
        }
	}

    MainFooter {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 24
        color: root.color
        textColor: 'white'
    }

/*
    Rectangle {
        id: leftSide
        border.color: 'gray'
        border.width: 2
        anchors.top: windowTitle.bottom

        Text {
            id: labelPackage
            text: qsTr("Package")
        }

        ComboBox {
            id: comboPackage
            anchors.top: labelPackage.bottom
        }

        Text {
            id: labelSearch
            text: qsTr("Search")
            anchors.top: comboPackage.bottom
        }

        TextInput {
            id: textSearch
            anchors.top: labelSearch.bottom
        }

        Text {
            id: labelResult
            text: qsTr("Result")
            anchors.top: textSearch.bottom
        }
    }
    */
}
