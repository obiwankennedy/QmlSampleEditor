import QtQuick
import QtQuick.Layouts

Item {
    id: root
    ColumnLayout {
        Repeater {
            model: 10
            Text {
                text: index
            }
        }
    }
}
