import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    color: "red"
    anchors.fill: parent

    Rectangle {
        color: "black"
        anchors.centerIn: parent
        width: 100
        height: width

        SequentialAnimation on width {
            loops: Animation.Infinite
            PropertyAnimation { to: root.width/2; duration: 800 }
            PropertyAnimation { to: root.width/4; duration: 300 }
        }
    }
}
