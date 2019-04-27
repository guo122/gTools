//====================================================================
//  main.qml
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import "./ODBox" as ODBox

Rectangle {
    height: 680
    width: 480
    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }

    LauncherList {
        id: ll
        anchors.fill: parent
        visible: dp.isOpen
        Component.onCompleted: {
            addExample("Time table", "",  Qt.resolvedUrl("TableTime.qml"));
            addExample("Goblin table", "",  Qt.resolvedUrl("TableGoblin.qml"));
            addExample("Efg table", "",  Qt.resolvedUrl("TableEfg.qml"));
        }
    }

    ODBox.DigitalPicker {
        id: dp
        theKey: ""
//        noEcho: true
    }
}
