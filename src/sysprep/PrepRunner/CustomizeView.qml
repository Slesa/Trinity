import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    padding: 5
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
                onClicked: runner.doSshKeys = checked
                Component.onCompleted: checked = runner.doSshKeys
            }
            CheckBox {
                height: 20
                text: qsTr("Install Fonts");
                onClicked: runner.doFonts = checked
                Component.onCompleted: checked = runner.doFonts
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
                onClicked: runner.doCorePrograms = checked
                Component.onCompleted: checked = runner.doCorePrograms
            }
            CheckBox {
                height: 20
                text: qsTr("X-Programs");
                onClicked: runner.doXPrograms = checked
                Component.onCompleted: checked = runner.doXPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("WM Programs");
                onClicked: runner.doWmPrograms = checked
                Component.onCompleted: checked = runner.doWmPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("TeX Programs");
                onClicked: runner.doTexPrograms = checked
                Component.onCompleted: checked = runner.doTexPrograms
            }
            CheckBox {
                height: 20
                text: qsTr("Games");
                onClicked: runner.doGames = checked
                Component.onCompleted: checked = runner.doGames
            }
        }
    }
}
