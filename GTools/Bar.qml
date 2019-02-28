//====================================================================
//  Bar.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.0
import "./GBox" as GBox

Rectangle {
    property string barHandle
    property string leftStr
    property string middleStr
    property variant middleModel
    property int middleModelSize: 0
    property string rightStr
    property string rightColor: "red"
    property variant rightModel
    property int rightModelSize: 0
    property alias rightComboText: rightCombo.text
    property alias middleComboText: middleCombo.text

    property var barHandleList: []
    property var middleStrList: []
    property var rightStrList: []
    property var rightColorList: []

    property var thisPtrList: []

    id: bar
    height: activePageCount > 0 ? 65 : 0
    width: parent.width
    visible: height > 0

    Behavior on height {
        NumberAnimation {
            duration: 100
        }
    }

    gradient: Gradient {
        GradientStop { position: 0 ; color: "#FFFFFFFF" }
        GradientStop { position: 1 ; color: "#000000FF" }
    }

    signal rightBtnClicked
    signal rightBtnDoubleClicked
    signal rightComboSelected(string comboxtext)
    signal middleComboSelected(string comboxtext)

    function back() {
        pageContainer.children[pageContainer.children.length - 1].exit()
        if (barHandleList.length)
        {
            barHandle = barHandleList.pop()
            middleStr = middleStrList.pop()
            rightStr = rightStrList.pop()
            rightColor = rightColorList.pop()
            thisPtrList.pop().update()
        }
    }

    function openUrl(thisPtr, url) {
        barHandleList.push(barHandle)
        middleStrList.push(middleStr)
        rightStrList.push(rightStr)
        rightColorList.push(rightColor)
        thisPtrList.push(thisPtr)
        ll.showExample(url)
    }

    Rectangle {
        height: 1
        color: "#AAA"
        anchors.bottom: bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        height: parent.height - 30
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        color: "transparent"

        GBox.TextButton {
            id: leftRect
            height: parent.height
            width: 80
            anchors.left: parent.left

            textStr: leftStr

            onTextClicked: {
                back()
            }
        }
        Rectangle {
            id: middleRect
            height: parent.height
            anchors.left: leftRect.right
            anchors.right: rightRect.left
            color: "transparent"

            Text {
                id: middleLable
                anchors.centerIn: parent
                visible: !middleCombo.visible
                text: middleStr
                font.pixelSize: 30
            }

            GBox.GCombo {
                id: middleCombo
                anchors.fill: parent
                visible: typeof(middleModel) != "undefined" && middleModelSize > 0

                listModel: middleModel
                listModelSize: middleModelSize

                onComboBoxTextChanged: {
                    middleComboSelected(comboxtext)
                }
            }
        }
        Rectangle {
            id: rightRect
            height: parent.height
            width: 80
            anchors.right: parent.right
            color: "transparent"

            GBox.TextButton {
                id: rightButton
                anchors.fill: parent
                visible: !rightCombo.visible

                textStr: rightStr
                textColor: rightColor

                onTextClicked: {
                    rightBtnClicked()
                }
                onTextDoubleClicked: {
                    rightBtnDoubleClicked()
                }
            }

            GBox.GCombo {
                id: rightCombo
                anchors.fill: parent
                visible: typeof(rightModel) != "undefined" && rightModelSize > 0

                listModel: rightModel
                listModelSize: rightModelSize
                listWidth: 160
                stableText: rightStr

                onComboBoxTextChanged: {
                    rightComboSelected(comboxtext)
                }
            }
        }
    }
}
