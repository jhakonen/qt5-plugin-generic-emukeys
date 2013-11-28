import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    property bool connected: false

    width: 150
    height: 200
    color: "white"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignCenter

            Text {
                text: "Host:"
            }

            Rectangle {
                border.width: 1
                implicitWidth: Math.max(contentId.implicitWidth, 100)
                implicitHeight: 20

                TextInput {
                    id: contentId
                    text: "localhost"
                    anchors.fill: parent
                    anchors.margins: 3

                    onTextChanged: keySender.setHost(text)
                }
            }
        }

        Button {
            id: powerOff
            text: qsTr("Power Off")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("power-off", true)
            onReleased: keySender.sendKeyEvent("power-off", false)
        }

        Button {
            id: volumeDown
            text: qsTr("Volume Down")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("volume-down", true)
            onReleased: keySender.sendKeyEvent("volume-down", false)
        }

        Button {
            id: volumeUp
            text: qsTr("Volume Up")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("volume-up", true)
            onReleased: keySender.sendKeyEvent("volume-up", false)
        }
    }

    onConnectedChanged: {
        powerOff.enabled = connected
        volumeDown.enabled = connected
        volumeUp.enabled = connected
    }
}
