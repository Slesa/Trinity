import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("First Application")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        id: settingsGroup
        anchors {
            margins: 20
            left: parent.left
            right: parent.right
        }
        height: 80
        color: 'grey'

        GroupBox {
            title: 'Settings'

            Row {
                id: currPath
                anchors.top: parent.top
                Text { text: 'Current Path:' }
                Text { text: currentPath }
            }
            Row {
                id: currWidth
                anchors.top: currPath.bottom
                Text { text: 'Width:' }
                Text { text: availableWidth }
            }
            Row {
                anchors.top: currWidth.bottom
                Text { text: 'Height:' }
                Text { text: availableHeight }
            }
        }
    }

    Rectangle {
        id: propertyGroup
        anchors {
            margins: 20
            top: settingsGroup.bottom
            left: parent.left
            right: parent.right
        }
        height: 60
        color: 'darkgrey'

        GroupBox {
            title: 'Property'

            Row {
                spacing: 5
                Text { text: 'New value:' }
                // 1. Variante: Update beim Schreiben
                TextInput {
                    id: prop
                    text: mainController.property
                    width: 160
                    Binding {
                        target: mainController
                        property: "property"
                        value: prop.text
                    }
                }
                Text { text: 'Current value:' }
                TextInput {
                    id: currVal
                    text: mainController.property
                    readOnly: true
                }
            }
        }
    }

    Rectangle {
        id: attributeGroup
        anchors {
            margins: 20
            top: propertyGroup.bottom
            left: parent.left
            right: parent.right
        }
        height: 60
        color: 'grey'
        GroupBox {
            id: groupAttrib
            title: 'Attribute'

            Row {
                spacing: 5
                Text {
                    text: 'Attribute:'
                    anchors.verticalCenter: parent.verticalCenter
                }
                // 2. Variante: Update per Funktionsaufruf
                TextInput {
                    id: attrib
                    text: mainController.attribute
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                }
                Button {
                    text: 'Set'
                    width: 60
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        mainController.changeAttribute(attrib.text);
                    }
                }
                Text {
                    text: 'Value:'
                    anchors.verticalCenter: parent.verticalCenter
                }
                TextInput {
                    text: mainController.attribute
                    anchors.verticalCenter: parent.verticalCenter
                    readOnly: true
                }
            }
        }
    }
}

