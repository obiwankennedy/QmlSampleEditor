import QtQuick
import QtQml.Models

Item {
    ListModel {
        id: colorModel
        ListElement { color: "blue"; x: 20; y: 20  }
        ListElement { color: "red"; x: 80; y: 30  }
        ListElement { color: "green"; x: 90; y: 70  }
    }

    Repeater {
        model: colorModel
        Rectangle {
            width: 30
            height: 30
            color: model.color
            x: model.x
            y: model.y
        }
    }
}
