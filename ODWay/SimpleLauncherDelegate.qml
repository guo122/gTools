//====================================================================
//  SimpleLauncherDelegate.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import ODVWay 1.0

Rectangle {
    id: container
    property Item exampleItem
    property string descriptionStr: ""
    property bool updateTrigger: true

    width: ListView.view.width
    height: button.implicitHeight + 22

    signal clicked()

    ODVMain { id: odvMain }

    Component.onCompleted: {
        if (description == "")
        {
            descriptionStr = odvMain.getDescription(name)
        }
        else
        {
            updateTrigger = false
            descriptionStr = description
        }
    }

    Item {
        Timer {
            interval: 500; running: updateTrigger; repeat: updateTrigger
            onTriggered: {
                descriptionStr = odvMain.getDescription(name)
            }
        }
    }

    gradient: Gradient {
        GradientStop {
            position: 0
            Behavior on color {ColorAnimation { duration: 100 }}
            color: button.pressed ? "#e0e0e0" : "#fff"
        }
        GradientStop {
            position: 1
            Behavior on color {ColorAnimation { duration: 100 }}
            color: button.pressed ? "#e0e0e0" : button.containsMouse ? "#f5f5f5" : "#eee"
        }
    }

    Image {
        id: image
        opacity: 0.7
        Behavior on opacity {NumberAnimation {duration: 100}}
//        source: "images/next.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 16
    }

    Item {
        id: button
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right:image.left
        implicitHeight: col.height
        height: implicitHeight
        width: buttonLabel.width + 20

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: container.clicked()
            hoverEnabled: true
        }

        Column {
            spacing: 2
            id: col
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            Text {
                id: buttonLabel
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: name
                color: "black"
                font.pixelSize: 22
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                styleColor: "white"
                style: Text.Raised

            }
            Text {
                id: buttonLabel2
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: descriptionStr
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: "#666"
                font.pixelSize: 12
            }
        }
    }

    Rectangle {
        height: 1
        color: "#ccc"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
