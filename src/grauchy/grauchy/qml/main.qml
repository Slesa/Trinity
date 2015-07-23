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
        id: mainHeader
		height: 24
        title: root.title
        winx: root.x
        winy: root.y
        color: root.color
        textColor: 'white'
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        onMoveWindow: {
            root.x = mainHeader.winx
            root.y = mainHeader.winy
        }
	}

    MainFooter {
        id: mainFooter
        height: 24
        color: root.color
        textColor: 'white'
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    MainContent {
        color: root.color
        anchors {
            left: parent.left
            right: parent.right
            top: mainHeader.bottom
            bottom: mainFooter.top
        }
    }

/*
    Rectangle {
        id: leftSide
        border.color: 'gray'
        border.width: 2
        anchors.top: mainHeader.bottom

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
