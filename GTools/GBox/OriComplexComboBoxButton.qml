//====================================================================
//  OriComplexComboBoxButton.qml
//  created 2.20.19
//  written by SadVSSmile
//
//  https://blog.csdn.net/u010655288/article/details/71686712
//====================================================================

import QtQuick 2.0

FocusScope {
    id: container
    signal clicked
    property alias source: image.source
    property alias text: label.text
    property color textColor: "white"
    property color borderColor: "limegreen"
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

        Image {
            id: image
            smooth: true
            fillMode: Image.PreserveAspectFit
            anchors{top: parent.top; right: parent.right; margins: container.margin;}
            width: parent.height; height: parent.height-2*container.margin
        }

        Item {
            anchors{top: parent.top; bottom: parent.bottom; left: parent.left; right: image.left; leftMargin: container.margin * 2;}
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

        states: State {
            name: "pressed"
            PropertyChanges { target: image; scale: 0.7 }
        }

        transitions: Transition {
            NumberAnimation { properties: "scale"; duration: 200; easing.type: Easing.InOutQuad }
        }
    }
}
