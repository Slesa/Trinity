import QtQuick 2.3
import QtQuick.Controls 1.2
import "components"

FocusScope {
    id: root
    height: 40
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        margins: 20
    }

    EditBox {
        id: editFilter
        focus: true
        activeFocusOnTab: true
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        KeyNavigation.tab: button
        KeyNavigation.backtab: root.parent
        onInputChanged: {
            buildingProxy.setFilterRegExp(text);
        }
    }
    IconButton {
        id: button
        anchors {
            left: editFilter.right
            verticalCenter: parent.verticalCenter
        }
        icon: 'qrc:/assets/clear.png'
        text: qsTr('Reset filter')
        KeyNavigation.tab: root.parent
        KeyNavigation.backtab: editFilter
        onClicked: {
            editFilter.text = '';
            editFilter.focus = true;
        }
    }
}
