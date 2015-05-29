import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1

    CheckBox {
        id: checkBox1
        x: 8
        y: 8
        text: qsTr("Check Box")
    }

    ComboBox {
        id: comboBox1
        x: 8
        y: 62
    }

    ProgressBar {
        id: progressBar1
        x: 8
        y: 95
    }

    GroupBox {
        id: groupBox1
        x: 8
        y: 294
        width: 284
        height: 154
        title: qsTr("Group Box")

        RowLayout {
            x: 82
            y: -63
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

    RadioButton {
        id: radioButton1
        x: 8
        y: 34
        text: qsTr("Radio Button")
    }

    SpinBox {
        id: spinBox1
        x: 280
        y: 35
        width: 81
        height: 25
    }

    ToolButton {
        id: toolButton1
        x: 392
        y: 144
    }

    TextArea {
        id: textArea1
        x: 8
        y: 192
        width: 240
        height: 96
    }

    Slider {
        id: sliderHorizontal1
        x: 8
        y: 158
    }

    TextField {
        id: textField1
        x: 8
        y: 125
        placeholderText: qsTr("Text Field")
    }

    Slider {
        id: sliderVertical1
        x: 585
        y: 184
        orientation: Qt.Vertical
    }

    Label {
        id: label1
        x: 231
        y: 39
        text: qsTr("Label")
    }

    GridView {
        id: gridView1
        x: 455
        y: 34
        width: 140
        height: 140
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        cellHeight: 70
        cellWidth: 70
        delegate: Item {
            x: 5
            height: 50
            Column {
                spacing: 5
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

    ListView {
        id: listView1
        x: 305
        y: 80
        width: 110
        height: 160
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
