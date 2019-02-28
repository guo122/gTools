//====================================================================
//  GComboButton.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.0

FocusScope {
    id: container
    signal clicked
    property alias text: label.text
    property color textColor: "black"
    property color borderColor: "transparent"
    property color backgroundColor: "transparent"
    property int borderWidth: 2
    property int textSize: 12
    property int radius: 5
    property int margin: 0

    Rectangle {
        id: buttonRectangle
        anchors.fill: parent
        color: container.backgroundColor
        radius: container.radius
        border{width: container.borderWidth; color: container.borderColor;}

        Item {
            anchors{top: parent.top; bottom: parent.bottom; left: parent.left; right: parent.right; leftMargin: container.margin * 2;}
            Text {
                id: label
                color: container.textColor
                anchors.centerIn: parent
                font{pixelSize: container.textSize-5; bold: true;}
            }
        }

        MouseArea {
            id: mouseArea;
            anchors.fill: parent
            onClicked: {
                buttonRectangle.state = "pressed"
                container.clicked()
            }
        }

        transitions: Transition {
            NumberAnimation { properties: "scale"; duration: 200; easing.type: Easing.InOutQuad }
        }
    }
}
