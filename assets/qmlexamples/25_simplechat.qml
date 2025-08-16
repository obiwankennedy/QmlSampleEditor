import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

SplitView {
    id: root
    orientation: Qt.Vertical

    ListModel {
        id: messages

    }

    Rectangle {
        SplitView.fillWidth: true
        SplitView.fillHeight: true
        border.width: 2
        color: "#77777744"

        ListView {
            id: listView
            anchors.fill: parent
            model: messages
            delegate: ItemDelegate {
                text: message
                width: listView.width
                height: 40
                background: Rectangle {
                    color:"blue"
                    opacity: 0.3
                    border.width: 2
                    radius: width/2
                }
            }
        }
    }

    RowLayout {
        SplitView.fillWidth: true
        SplitView.minimumHeight: 150
        TextArea {
            id: textArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                radius: 8
                border.width: 2

            }
        }
        Button {
            text: qsTr("Send")
            Layout.fillHeight: true
            onClicked: {
                console.log("On clicked")
                messages.append({"message": textArea.text})
                textArea.text = ""
            }
        }
    }

}
