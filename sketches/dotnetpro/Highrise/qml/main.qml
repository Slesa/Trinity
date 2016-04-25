import QtQuick 2.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    id: root
    visible: true
    title: qsTr("HighRise")
    width: 640
    height: 480

    RadialGradient {
           anchors.fill: parent
           horizontalOffset: root.width/2
           verticalOffset: root.height/2
           horizontalRadius: root.width
           verticalRadius: root.height
           gradient: Gradient {
               GradientStop {
                   position: 0.0;
                   color: "#2A2C63"
               }
               GradientStop {
                   position: 1.0;
                   color: "#3D8CCB"
               }
           }
    }

    BuildingView {
        anchors.fill: parent
    }
}

