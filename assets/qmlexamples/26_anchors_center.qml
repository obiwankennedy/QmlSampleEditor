import QtQuick 2.12

Rectangle {
    anchors.fill: parent

    Rectangle {
        width: 500
        height: 500
        color: "white"
        border.width: 2
        anchors.centerIn: parent
        
        Rectangle {
            width: 20
            height: 10
            color: "blue"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Rectangle {
            width: 20
            height: 10
            color: "green"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
