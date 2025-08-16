import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml.Models

Item {
    anchors.fill: parent

    ListModel{
        id: imgs
        ListElement {
            url:"https://upload.wikimedia.org/wikipedia/commons/0/07/Emperor_Penguin_Manchot_empereur.jpg"
            name: "Emperor"
        }
        ListElement {
            url:"https://upload.wikimedia.org/wikipedia/commons/6/6f/011_The_lion_king_Tryggve_in_the_Serengeti_National_Park_Photo_by_Giles_Laurent.jpg"
            name: "King"
        }
        ListElement {
            url:"https://upload.wikimedia.org/wikipedia/commons/7/77/Big-eared-townsend-fledermaus.jpg"
            name: "Vampire"
        }
        ListElement {
            url:"https://upload.wikimedia.org/wikipedia/commons/0/06/Blue_Whale_001_body_bw.jpg"
            name: "Biggest"
        }
        ListElement {
            url:"https://upload.wikimedia.org/wikipedia/commons/b/b1/Male_mallard_standing.jpg"
            name: "Duck Pick"
        }
    }


    Component {
        id: delegate
        Item {
            width: parent.width*0.8
            height: parent.height*0.8
            property double rotationValue2: PathView.itemRotation
            scale: PathView.iconScale
            opacity: PathView.isCurrentItem ? PathView.itemOpacity : 0.3
            z: PathView.isCurrentItem ? 5 : 0
            transform: Rotation {
                origin.x: width /2
                origin.y: height/2
                axis { x: 0; y: 1; z: 0 }
                angle: rotationValue2;
            }
            Image {
                id: _img
                anchors.fill: parent
                source: model.url
                fillMode: Image.PreserveAspectFit
            }
            Label {
                anchors.top: _img.bottom
                anchors.horizontalCenter: _img.horizontalCenter
                font.pointSize: 30
                text: model.name
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = index;
                }
            }

        }
    }

    PathView {
        id: view
        anchors.fill: parent
        path: Path {
            startX: view.width/2
            startY: view.height/2
            PathAttribute { name: "iconScale"; value: 1.0 }
            PathAttribute { name: "itemOpacity"; value: 1 }
            PathAttribute { name: "itemRotation"; value: 0.0 }
            PathLine { x:view.width; y: 3*view.height/8 }
            PathAttribute { name: "iconScale"; value: 0.3 }
            PathAttribute { name: "itemOpacity"; value: 0.001 }
            PathAttribute { name: "itemRotation"; value: -54 }
            PathLine { x: 0; y: 3*view.height/8; }
            PathAttribute { name: "iconScale"; value: 0.3 }
            PathAttribute { name: "itemOpacity"; value: 0.001 }
            PathAttribute { name: "itemRotation"; value: 54 }
            PathLine { x: view.width*0.5; y: view.height*0.5; }
        }

        delegate: delegate
        focus: true
        Keys.onLeftPressed: incrementCurrentIndex()
        Keys.onRightPressed: decrementCurrentIndex()
        model: imgs
    }

}

