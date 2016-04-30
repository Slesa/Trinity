import QtQuick 2.4

// http://stackoverflow.com/questions/17833103/how-to-create-scrollbar-in-qtquick-2-0
Item {
    id: scrollBar

    width: (handleSize + 2 * (backScrollbar.border.width +1));
    visible: (flickable.visibleArea.heightRatio < 1.0);

    anchors {
        top: flickable.top;
        topMargin: 1;
        right: flickable.right;
        bottom: flickable.bottom;
        bottomMargin: 1;
    }

    property Flickable flickable: null;
    property int handleSize: 7;

    function scrollDown () {
        flickable.contentY = Math.min (flickable.contentY + (flickable.height / 4), flickable.contentHeight - flickable.height);
    }
    function scrollUp () {
        flickable.contentY = Math.max (flickable.contentY - (flickable.height / 4), 0);
    }

   Binding {
        target: handle;
        property: "y";
        //value: !isNaN(flickable.visibleArea.heightRatio) ? (clicker.drag.maximumY * flickable.contentY) / (flickable.contentHeight * (1 - flickable.visibleArea.heightRatio)) : 0
        value: (flickable.contentY * clicker.drag.maximumY / (flickable.contentHeight - flickable.height));
        when: (!clicker.drag.active);
    }
    Binding {
        target: flickable;
        property: "contentY";
        value: (( flickable.contentHeight * (1 - flickable.visibleArea.heightRatio)) * handle.y) / clicker.drag.maximumY
        //value: (handle.y * (flickable.contentHeight - flickable.height) / clicker.drag.maximumY);
        when: (clicker.drag.active || clicker.pressed);
    }

   Rectangle {
        id: backScrollbar;
        antialiasing: true;
        anchors { fill: parent; }

        MouseArea {
            anchors.fill: parent;
            onClicked: { }
        }
    }

   MouseArea {
        id: buttonUp;
        height: 12;
        hoverEnabled: true
        anchors {
            top: parent.top;
            left: parent.left;
            right: parent.right;
            margins: (backScrollbar.border.width +1);
        }
        onClicked: { scrollUp (); }

        Image {
            height: parent.height
            //source: buttonUp.containsMouse ? Icons.iconArrowUpHover : Icons.iconArrowUpNormal
            fillMode: Image.PreserveAspectCrop
        }
    }
    MouseArea {
        id: buttonDown;
        height: 12;
        hoverEnabled: true
        anchors {
            left: parent.left;
            right: parent.right;
            bottom: parent.bottom;
            margins: (backScrollbar.border.width +1);
        }
        onClicked: { scrollDown (); }

        Image {
            height: parent.height
            //source: buttonDown.containsMouse ? Icons.iconArrowDownHover : Icons.iconArrowDownNormal
            fillMode: Image.PreserveAspectCrop
        }
    }
    Item {
        id: groove;
        clip: true;
        anchors {
            fill: parent;
            topMargin: (backScrollbar.border.width +1 + buttonUp.height +1);
            leftMargin: (backScrollbar.border.width +1);
            rightMargin: (backScrollbar.border.width +1);
            bottomMargin: (backScrollbar.border.width +1 + buttonDown.height +1);
        }

        MouseArea {
            id: clicker;
            hoverEnabled: true
            drag {
                target: handle;
                minimumY: 0;
                maximumY: (groove.height - handle.height);
                axis: Drag.YAxis;
            }
            anchors { fill: parent; }
            onClicked: { flickable.contentY = (mouse.y / groove.height * (flickable.contentHeight - flickable.height)); }
        }
        Item {
            id: handle;
            height: Math.max (20, (flickable.visibleArea.heightRatio * groove.height));
            anchors {
                left: parent.left;
                right: parent.right;
            }

            Rectangle {
                id: backHandle;
                color: 'blue' // clicker.containsMouse ? Colors.brushTextHover : Colors.brushTextInactive // (clicker.pressed ? "blue" : "black");
                opacity: 0.7 // (flickable.moving ? 0.65 : 0.35);
                anchors { fill: parent; }

                Behavior on opacity { NumberAnimation { duration: 150; } }
            }
        }
    }
}
