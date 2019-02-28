//====================================================================
//  GTRandomListList.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.9
import GTVRandomList 1.0
import "./GBox" as GBox

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    GTVRandomListQML { id: gtvRandomList }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = ""
        bar.rightStr = ""
        bar.rightColor = "black"
        bar.rightModelSize = 0
        bar.barHandle = "handleTableRandomListList"
        bar.middleModel = gtvRandomList.getKindList()
        bar.middleModelSize = gtvRandomList.getKindSize()

        tableRandomListView.model = gtvRandomList.getNameList(bar.middleComboText)
    }

    Connections{
        target: bar
        onMiddleComboSelected:{
            if (bar.barHandle == "handleTableRandomListList")
            {
                tableRandomListView.model = gtvRandomList.getNameList(bar.middleComboText)
            }
        }
    }

    Component {
        id: tableRandomListViewDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 20
            color: "transparent"
            Text {
                id: wrapperText
                width: parent.width
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tableRandomListView.currentIndex = index
                    wrapperText.color = "black"
                }
            }

            // indent the item if it is the current item
            states: [
                State {
                    name: "Current"
                    when: wrapper.ListView.isCurrentItem
                    PropertyChanges {
                        target: wrapperText
                        font.bold: true
                        font.underline: true
                        color: "black"
                    }
                }
            ]
        }
    }


    ListView {
        id: tableRandomListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        delegate: tableRandomListViewDelegate
    }
}
