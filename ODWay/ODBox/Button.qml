//====================================================================
//  Button.qml
//  created 6.9.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0

Rectangle {
    id: button
    signal clicked
    property alias text: txt.text
    property bool buttonEnabled: false
    width: Math.max(64, txt.width + 16)
    height: 32
    color: "transparent"
    MouseArea {
        anchors.fill: parent
        onClicked: button.clicked()
    }
    Text {
        anchors.centerIn: parent
        font.pointSize: 19
        font.weight: Font.DemiBold
        color: button.buttonEnabled ? "#000000" : "#14aaff"
        id: txt
    }
}
