import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    padding: 5
    spacing: 5
    GroupBox {
        title: qsTr("Settings")
        width: parent.width
        Column {
            padding: 5
            spacing: 0
            CheckBox {
                text: qsTr("Generate SSH Key");
                onClicked: runner.doSshKeys = checked
                Component.onCompleted: checked = runner.doSshKeys
            }
            CheckBox {
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
                text: qsTr("Core programs");
                onClicked: runner.doCorePrograms = checked
                Component.onCompleted: checked = runner.doCorePrograms
            }
            CheckBox {
                text: qsTr("X-Programs");
                onClicked: runner.doXPrograms = checked
                Component.onCompleted: checked = runner.doXPrograms
            }
            CheckBox {
                text: qsTr("WM Programs");
                onClicked: runner.doWmPrograms = checked
                Component.onCompleted: checked = runner.doWmPrograms
            }
            CheckBox {
                text: qsTr("TeX Programs");
                onClicked: runner.doTexPrograms = checked
                Component.onCompleted: checked = runner.doTexPrograms
            }
            CheckBox {
                text: qsTr("Games");
                onClicked: runner.doGames = checked
                Component.onCompleted: checked = runner.doGames
            }
        }
    }
}
