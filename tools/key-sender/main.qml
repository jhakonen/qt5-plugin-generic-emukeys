import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: 150
    height: 200
    color: "white"

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: qsTr("Power Off")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("power-off", true)
            onReleased: keySender.sendKeyEvent("power-off", false)
        }

        Button {
            text: qsTr("Volume Down")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("volume-down", true)
            onReleased: keySender.sendKeyEvent("volume-down", false)
        }

        Button {
            text: qsTr("Volume Up")
            Layout.alignment: Qt.AlignCenter

            onPressed: keySender.sendKeyEvent("volume-up", true)
            onReleased: keySender.sendKeyEvent("volume-up", false)
        }
    }
}
