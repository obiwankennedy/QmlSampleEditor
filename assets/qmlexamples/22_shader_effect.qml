import QtQuick
import QtQuick.Controls

Rectangle {
    color: "grey"
    anchors.fill: parent

    Rectangle {
        anchors.centerIn : parent
        color: "white"
        width: 400
        height: 400
        Image {
            id: pix
            source: "https://upload.wikimedia.org/wikipedia/commons/0/07/Emperor_Penguin_Manchot_empereur.jpg"
            visible:false
        }

        ShaderEffect {
            id: shader
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            readonly property Item iSource: pix
            vertexShader: "qrc:/assets/blackandwhite.vert.qsb"
            fragmentShader: "qrc:/assets/blackandwhite.frag.qsb"
            onLogChanged: console.log("shader:log:",shader.log)
        }
    }
}
