import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import de.slesa.io 1.0

ApplicationWindow {
    id: root
    title: qsTr("City UI")
    width: 640; height: 480
    visible: true

    Action {
        id: save
        text: qsTr("&Save")
        shortcut: StandardKey.Save
        onTriggered: saveDocument()
    }

    Action {
        id: open
        text: qsTr("&Open")
        shortcut: StandardKey.Open
        onTriggered: openDialog.open()
    }

    Action {
        id: exit
        text: qsTr("E&xit")
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit();
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: open }
            MenuItem { action: save }
            MenuSeparator {}
            MenuItem { action: exit }
        }
    }

    TableView {
        id: view
        anchors.fill: parent
        TableViewColumn {
            role: 'city'
            title: qsTr("City")
            width: 120
        }
        TableViewColumn {
            role: 'country'
            title: qsTr("Country")
            width: 120
        }
        TableViewColumn {
            delegate: Item {
                Image {
                    anchors.centerIn: parent
                    source: 'flags/' + styleData.value
                }
            }
            role: 'flag'
            title: qsTr("Flag")
            width: 40
        }
        TableViewColumn {
            role: 'area'
            title: qsTr("Area")
            width: 80
        }
        TableViewColumn {
            role: 'population'
            title: qsTr("Population")
            width: 80
        }
        TableViewColumn {
            delegate: Button {
                iconSource: "remove.png"
                opacity: !mouseArea.containsMouse ? 0.5 : 1.0
                scale: !mouseArea.containsMouse ? 0.5 : 1.0
                smooth: !mouseArea.containsMouse
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    anchors.margins: -10
                    hoverEnabled: true
                    onClicked: {
                        var data = view.model
                        data.splice(styleData.row, 1)
                        view.model = data
                    }
                }
            }
            width: 40
        }
    }

    FileDialog {
        id: openDialog
        onAccepted: {
            root.readDocument()
        }
    }

    function readDocument() {
        console.debug(openDialog.fileUrl)
        io.source = openDialog.fileUrl
        io.read()
        view.model = JSON.parse(io.text)
    }

    function saveDocument() {
        var data = view.model
        io.text = JSON.stringify(data, null, 4)
        io.write()
    }

    FileIO {
        id: io
    }
}
