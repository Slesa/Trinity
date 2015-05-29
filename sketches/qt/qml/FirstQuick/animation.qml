import QtQuick 2.0

Rectangle {
    width: 800
    height: 480

    Image {
        source: "assets/background.png"

        Image {
            x: 40; y:80
            source: "assets/rocket.png"

            NumberAnimation on x {
                to: 240
                duration: 4000
                loops: Animation.Infinite
            }
            RotationAnimation on rotation {
                to: 360
                duration: 4000
                loops: Animation.Infinite
            }
            NumberAnimation on scale {
                to: 0.5
                duration: 4000
                loops: Animation.Infinite
            }
        }
    }
}

