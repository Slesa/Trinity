import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Item {
    id: root
    width: 100
    height: 62

    property alias name: check.text
    property int occurances: 0

    CheckBox {
        id: check
        text: "Filter"
        anchors.left: parent.Left
        style: CheckBoxStyle {
            label: Text {
                color: check.checked? "black" : "white"
            }
        }
    }

    Text {
        id: count
        anchors.left: cb.width
        anchors.right: parent.right
        text: "(" + root.occurances + ")"
        style: cb.style
    }

}

