import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
//    padding: 5
    spacing: 5
    height: parent.height
    GroupBox {
        title: qsTr("Settings")
        width: parent.width
        Column {
            padding: 5
            spacing: 0
            CheckBox {
                height: 20
                text: qsTr("Generate SSH Key");
                onClicked: settings.doSshKeys = checked
                Component.onCompleted: checked = settings.doSshKeys
            }
            CheckBox {
                height: 20
                text: qsTr("Install Fonts");
                onClicked: settings.doFonts = checked
                Component.onCompleted: checked = settings.doFonts
            }
        }
    }
    GroupBox {
        title: qsTr("Packages")
        width: parent.width

        Column {
            padding: 5
            spacing: 0
            CheckBox {
                height: 20
                text: qsTr("Core programs");
                onClicked: settings.doCorePrograms = checked
                Component.onCompleted: checked = settings.doCorePrograms
            }
            CheckBox {
                height: 20
                text: qsTr("X-Programs");
                onClicked: settings.doXPrograms = checked
                Component.onCompleted: checked = settings.doXPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("WM Programs");
                onClicked: settings.doWmPrograms = checked
                Component.onCompleted: checked = settings.doWmPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("TeX Programs");
                onClicked: settings.doTexPrograms = checked
                Component.onCompleted: checked = settings.doTexPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("Games");
                onClicked: settings.doGames = checked
                Component.onCompleted: checked = settings.doGames
            }
        }
    }
}
