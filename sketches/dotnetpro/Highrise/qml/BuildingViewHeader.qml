import QtQuick 2.3
import QtQuick.Controls 1.2
import "components"

FocusScope {
    id: root
//    color: 'transparent'
    height: 40
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        margins: 20
    }
/*    Rectangle {
        id: inputLine
        anchors {
            fill: parent
            margins: 20
        }*/
        /*{
            left: parent.left
            leftMargin: 10
            top:
        }*/

        EditBox {
            id: editFilter
            focus: true
            activeFocusOnTab: true
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            KeyNavigation.tab: button
            //text: buildingProxy.filterRegExp
            //hint: qsTr('Filter')
            onInputChanged: {
                console.debug("Text changed");
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
            KeyNavigation.backtab: editFilter
            onClicked: {
                console.debug("Clear filter");
                editFilter.text = '';
                editFilter.focus = true;
            }
        }
//    }
}
