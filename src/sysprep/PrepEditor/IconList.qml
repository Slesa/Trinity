import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    ListView {
        anchors.fill: parent
        model: 20
        delegate: ItemDelegate {
            Button {
                icon.name: "package"
                text: "Item " + (index + 1)
                width: 80
                height: 30
            }
        }

        //headerPositioning: ListView.OverlayHeader
        header: Rectangle {
            width: browser.width
            height: 34
            color: "yellow"
            z:2
            Row {
                anchors.fill: parent
                Button {
                    width:32
                    height :32
                    text: "<<<"
                    //onClicked: view.path = folder.parentFolder
                }
                Text {
                    text: "Hello" //view.path
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        // footerPositioning: ListView.OverlayHeader
        footer: Rectangle {
            width: browser.width
            height: 34
            color: "yellow"
            z:2
            Row {
                anchors.fill: parent
                Text {
                    text: "World" //"["+folder.count+" Files]"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
