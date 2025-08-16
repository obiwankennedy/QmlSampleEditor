import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "pink"
    anchors.fill: parent
    property var msgs: []

    TapHandler {
        onTapped: newMsg("Left click!")
    }
    TapHandler {
        acceptedButtons: Qt.RightButton
        onTapped: newMsg("Right click!")
    }

    function newMsg(msg) {
            console.log(msg)
            msgs.push(msg)
            // We need to force a *Changed* signal for normal js lists
            view.model = msgs
    }

    ListView {
        id: view
        height: parent.height
        delegate: Text {
            text: index + ": " + modelData
        }
    }
}
