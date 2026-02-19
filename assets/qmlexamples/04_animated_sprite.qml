import QtQuick

Rectangle {
    anchors.fill: parent

    AnimatedSprite {
        id: animation
        source: "qrc:/dico/assets/sprites.png"
        anchors.centerIn: parent
        width: 100
        height: 100
        frameWidth: 200
        frameHeight: 745/3
        frameCount: 13
        frameDuration: 100
        reverse: false
        loops: 20
    }
}
