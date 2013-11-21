import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: 360
    height: 360
    color: "white"

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            text: qsTr("Following buttons will change when button events are received.")
            wrapMode: Text.Wrap
            Layout.fillWidth: true
        }

        ButtonIndicator {
            id: powerOff
            text: qsTr("Power Off")
            Layout.alignment: Qt.AlignCenter
        }

        ButtonIndicator {
            id: volumeDown
            text: qsTr("Volume Down")
            Layout.alignment: Qt.AlignCenter
        }

        ButtonIndicator {
            id: volumeUp
            text: qsTr("Volume Up")
            Layout.alignment: Qt.AlignCenter
        }

        Connections {
            target: keySource
            onPowerKeyReceived: {
                powerOff.flash()
                powerOff.isPressed = pressed
            }
            onVolumeDownKeyReceived: {
                volumeDown.flash()
                volumeDown.isPressed = pressed
            }
            onVolumeUpKeyReceived: {
                volumeUp.flash()
                volumeUp.isPressed = pressed
            }
        }
    }
}
