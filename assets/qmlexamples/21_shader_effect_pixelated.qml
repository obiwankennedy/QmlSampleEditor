import QtQuick
import QtQuick.Controls

Rectangle {
    color: "grey"
    anchors.fill: parent



    Rectangle {
        id: centerRect
        anchors.centerIn : parent
        color: "white"
        width: 400
        height: 400
        Image {
            id: pix
            source: "https://upload.wikimedia.org/wikipedia/commons/0/07/Emperor_Penguin_Manchot_empereur.jpg"
            anchors.fill: parent
            visible:false
        }


        ShaderEffect {
            id: shader
            anchors.fill: parent
            readonly property Item iSource: pix
            readonly property real pixelSize: slider.value
            readonly property vector3d iResolution: Qt.vector3d(width, height, 1.0)
            vertexShader: "qrc:/assets/pixelize.vert.qsb"
            fragmentShader: "qrc:/assets/pixelize.frag.qsb"
            onLogChanged: console.log("shader:log:",shader.log)
        }
    }

    Slider {
        id: slider
        from: 1
        to: 100
        value: 10
        anchors.margins: 100
        anchors.bottom: centerRect.top
        anchors.left: centerRect.left
    }
}

