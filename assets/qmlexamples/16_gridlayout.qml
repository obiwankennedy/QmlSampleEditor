import QtQuick
import QtQml
import QtQuick.Layouts

GridLayout {
    id: root
    rows: 5
    columns: 5
    anchors.fill: parent
    columnSpacing: 0
    rowSpacing: 0



    Repeater {
        id: repeater
        model: parent.rows * parent.columns
        Rectangle {
            id: rect
            property real value: index / repeater.model
            color: Qt.hsva(value, value, value)
            Layout.preferredWidth: root.width / root.columns
            Layout.preferredHeight: root.height / root.rows
        }
    }
}
