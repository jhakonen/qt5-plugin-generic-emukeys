import QtQuick 2.0

Rectangle {
    property string text
    signal pressed
    signal released

    implicitWidth: textId.implicitWidth + 20
    implicitHeight: textId.implicitHeight + 20

    color: "grey"
    gradient: gradientUp
    border.color: "darkgrey"
    border.width: 2
    radius: 5

    Gradient {
        id: gradientUp
        GradientStop { position: 0.0; color: "lightgrey" }
        GradientStop { position: 1.0; color: "grey" }
    }

    Text {
        id: textId
        anchors.centerIn: parent
        text: parent.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            parent.gradient = undefined
            parent.pressed()
        }
        onReleased: {
            parent.gradient = gradientUp
            parent.released()
        }
    }
}
