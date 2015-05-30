import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1

    GroupBox {
        id: groupBox1
        x: 8
        y: 399
        width: 271
        height: 73
        title: qsTr("Group Box")

        RowLayout {
            x: 10
            y: 185
            anchors.centerIn: parent

            Button {
                id: button1
                text: qsTr("Press Me 1")
            }

            Button {
                id: button2
                text: qsTr("Press Me 2")
            }

            Button {
                id: button3
                text: qsTr("Press Me 3")
            }
        }
    }

    CheckBox {
        id: checkBox1
        x: 8
        y: 8
        text: qsTr("Check Box")
    }
    DoubleSlider {
        id: doubleSlider1
        x: 233
        y: 322
        color: "#9fe431"
    }
}
