//====================================================================
//  main.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.9
import "./GBox" as GBox

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
        Component.onCompleted: {
            addExample("Random", "",  Qt.resolvedUrl("GTRandomListData.qml"));
            addExample("RandomAdd", "",  Qt.resolvedUrl("GTRandomListAdd.qml"));
            addExample("RandomList", "",  Qt.resolvedUrl("GTRandomListList.qml"));
        }
    }
}
