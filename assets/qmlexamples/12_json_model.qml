import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    property var parameters: undefined

    anchors.fill: parent

    ScrollView {
        id: scroll

        height: parent.height

        ColumnLayout {
            id: parameterButton

            Repeater {
                model: root.parameters ? Object.keys(root.parameters['people']) : undefined

                Button {
                    text: modelData

                    Layout.fillWidth: true

                    onClicked: {
                        textContent.text = JSON.stringify(root.parameters['people'][modelData], null, 2)
                    }
                }
            }
        }
    }

    Text {
        id: textContent

        anchors.left: scroll.right
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

    function getJson() {
        var xmlhttp = new XMLHttpRequest();
        var url = "https://raw.githubusercontent.com/obiwankennedy/QmlSampleEditor/refs/heads/main/assets/Data.json";

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState == XMLHttpRequest.DONE && xmlhttp.status == 200) {
                root.parameters = JSON.parse(xmlhttp.responseText)
                progressBar.visible = false
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.send();
    }

    ProgressBar {
        id: progressBar

        width: parent.width
        anchors.verticalCenter: parent.verticalCenter

        indeterminate: true

        Label {
            text: "loading..."

            font.pixelSize: 30

            anchors.margins: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.bottom
            Layout.fillWidth: true
        }
    }

    Component.onCompleted: getJson()
}
