//====================================================================
//  TextButtonNoDouble.qml
//  created 6.16.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0

Rectangle {
    property string textStr: ""
    property int textSize: 22
    property bool textBold: true
    property string textColor: "black"
    property string textBKColor: "transparent"
    property bool textVisible: true
    property bool textAlwayEnabled: false

    signal textClicked
    signal textLongPress

    color: textBKColor

    Text {
        anchors.centerIn: parent

        visible: textVisible
        text: textStr
        font.pixelSize: textSize
        font.bold: textBold
        color: textColor
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        anchors.verticalCenterOffset: -1
        enabled: textStr != "" || textAlwayEnabled

        onClicked: textClicked()
        onPressAndHold: textLongPress()

        Rectangle {
            anchors.fill: parent
            visible: textVisible
            opacity: parent.pressed ? 1 : 0
            Behavior on opacity { NumberAnimation{ duration: 100 }}
            gradient: Gradient {
                GradientStop { position: 0 ; color: "#22000000" }
                GradientStop { position: 0.2 ; color: "#11000000" }
            }
            border.color: "darkgray"
            antialiasing: true
            radius: 4
        }
    }
}
