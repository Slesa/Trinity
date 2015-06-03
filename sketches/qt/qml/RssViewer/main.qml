import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.XmlListModel 2.0

ApplicationWindow {
    title: qsTr("RSS Viewer")
    width: 640
    height: 480
    visible: true

    Rectangle {
        anchors.fill: parent
        color: "white"

        ListView {
            id: listviewRss
            anchors.fill: parent
            focus: true
            orientation: ListView.Vertical
            model: xmlModel
            delegate: Text { text: pubDate + ": " + title }
        }
    }

    XmlListModel {
        id: xmlModel
//        source: "http://www.heise.de/newsticker/heise-atom.xml"
//        source: "http://heise.de.feedsportal.com/c/35207/f/653902/index.rss"
        source: "feed.rss"
        query: "/rss/channel/item"
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "guid"; query: "guid/string()" }
        XmlRole { name: "link"; query: "link/string()" }
        XmlRole { name: "pubDate"; query: "pubDate/string()" }
    }
}
