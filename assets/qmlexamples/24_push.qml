import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    SwipeView {
        id: swipe
        anchors.fill: parent
        Page {
            title: "First Page"
            Rectangle {
                anchors.fill: parent
                Label {
                    text: "First Page"
                    anchors.centerIn: parent
                }
            }
        }
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
            }
        }
        Page {
            title: "Third Page"
            Rectangle {
                color: "green"
                anchors.fill: parent
                Label {
                    text: "Third Page"
                    color: "white"
                    anchors.centerIn: parent
                }
            }
        }
        Page {
            title: "Forth Page"
            Rectangle {
                color: "orange"
                anchors.fill: parent
                Label {
                    text: "Forth Page"
                    color: "white"
                    anchors.centerIn: parent
                }
            }
        }
    }

    PageIndicator {
        id: indicator

        count: swipe.count
        currentIndex: swipe.currentIndex

        anchors.bottom: swipe.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
