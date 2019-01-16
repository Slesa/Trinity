import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    IconList {
        anchors.fill: parent
    }

    /*
    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                Button {
                    icon.name: "package"
                    text: "Item " + (index + 1)
                    width: 40
                    height: 30
                }
            }
        }
    } */
}
