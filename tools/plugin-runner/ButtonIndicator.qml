import QtQuick 2.0

// ButtonIndicator
Rectangle {
    id: topReactangle
    property string text
    property bool isPressed

    function flash() {
        flashAnimation.start()
    }

    // calculate indicator's preferred size
    implicitWidth: textId.width + 30 * 2
    implicitHeight: textId.height + 30 * 2

    border.width: 2
    border.color: "white"

    Text {
        id: textId
        text: parent.text
        anchors.centerIn: parent
    }

    PropertyAnimation {
        id: flashAnimation
        target: topReactangle
        property: "border.color"
        from: "black"
        to: topReactangle.border.color
    }

    onIsPressedChanged: color = isPressed? "red": "transparent"
}
