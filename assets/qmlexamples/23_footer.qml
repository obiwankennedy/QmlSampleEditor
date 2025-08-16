import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    Component {
        id: page1
        Page {
            title: "First Page"
            Rectangle {
                anchors.fill: parent
                Label {
                    text: "First Page"
                    anchors.centerIn: parent
                }
                Button {
                    text: "next"
                    onClicked:stack.push(page2)
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 40
                }
            }
        }
    }
    Component {
        id: page2
        Page {
            title: "Second Page"
            Rectangle {
                color: "red"
                anchors.fill: parent
                Label {
                    text: "Second Page"
                    color: "white"
                    anchors.centerIn: parent
                }
                Button {
                    text: "next"
                    enabled: false
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 40
                }
                Button {
                    text: "previous"
                    onClicked:stack.pop()
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.margins: 40
                }
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent

        initialItem: page1
    }
}
