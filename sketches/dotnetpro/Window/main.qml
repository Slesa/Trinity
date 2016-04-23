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
        color: 'lightgrey'

        GroupBox {
            title: 'Property'

            Row {
                Text { text: 'New value:' }
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
                Text { text: 'Attribute:' }
                TextInput {
                    id: attrib
                    text: mainController.attribute
                    width: 160
                }
                Button {
                    text: 'Set'
                    onClicked: {
                        mainController.changeAttribute(attrib.text);
                    }
                }
                Text { text: 'Value:' }
                TextInput {
                    text: mainController.attribute
                    readOnly: true
                }
            }
        }
    }
}

