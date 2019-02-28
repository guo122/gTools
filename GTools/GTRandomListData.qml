//====================================================================
//  GTRandomListData.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4
import GTVRandomList 1.0
import "./GBox" as GBox

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    GTVRandomListQML { id: gtvRandomList }

    function initRandomData() {
        if (bar.rightComboText == "Rand") {
            gtvRandomList.initRandomList(bar.middleComboText, 1)  // mode 1 is rand
        }
        if (bar.rightComboText == "Plan") {
            gtvRandomList.initRandomList(bar.middleComboText, 2)  // mode 1 is rand
        }
    }

    function updateRandomData() {
        nextButton.textStr = gtvRandomList.getRandom()
        nextButton.textSize = gtvRandomList.getRandomFontSize()
        if (gtvRandomList.getRandomProgress() >= 0)
        {
            randomProgress.visible = true
            randomProgress.value = gtvRandomList.getRandomProgress()
        }
        else
        {
            randomProgress.visible = false
        }
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = ""
        bar.rightStr = ""
        bar.rightColor = "black"
        bar.rightModel = ["Rand", "Plan"]
        bar.rightModelSize = 2
        bar.middleModel = gtvRandomList.getKindList()
        bar.middleModelSize = gtvRandomList.getKindSize()
        bar.barHandle = "handleTableRandomListData"

        initRandomData()
        updateRandomData()
    }

    Connections{
        target: bar
        onMiddleComboSelected:{
            if (bar.barHandle == "handleTableRandomListData")
            {
                initRandomData()
                updateRandomData()
            }
        }
        onRightComboSelected:{
            if (bar.barHandle == "handleTableRandomListData")
            {
                initRandomData()
                updateRandomData()
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        color: "transparent"

        GBox.TextButtonNoDouble {
            id: nextButton
            anchors.fill: parent
            textStr: "NEXT"

            onTextClicked: {
                updateRandomData()
            }
        }

        ProgressBar {
            id: randomProgress
            width: parent.width
            anchors.bottom: parent.bottom
            minimumValue: 0
            maximumValue: 100
            visible: false
        }
    }
}
