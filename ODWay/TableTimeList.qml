//====================================================================
//  TableTimeList.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import "./ODBox" as ODBox

Rectangle {
    // 0: default; 1: durMode; 2: deleteMode
    property bool selectMode: false
    property int index1: 0
    property int index2: 0
    property var lastWrapper
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Component.onCompleted: {
        // list
        updateCurList()
        bar.leftStr = "<"
        bar.middleStr = odvTimeList.runningTimeStr
        bar.rightStr = ""
        bar.barHandle = "handleTableTimeList"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeList" && bar.rightStr == "x")
            {
                selectMode = false
                bar.rightColor = "red"
                bar.rightStr = ""
                tableTimeListView.currentIndex = 0
                lastWrapper.color = "transparent"
            }
            else if (bar.barHandle == "handleTableTimeList" && bar.rightStr == "Del")
            {
                if (odvTimeList.delTime(tableTimeListView.currentIndex))
                {
                    updateCurList()
                    bar.rightStr = ""
                }
            }
        }
    }

    function updateCurList() {
        tableTimeListView.model = ""
        odvTimeList.updateList()
        tableTimeListView.model = odvTimeList.curList
        selectMode = false
        bar.rightColor = "red"
        bar.rightStr = ""
        tableTimeListView.currentIndex = 0
    }

    function endList() {
        if (lastWrapper)
        {
            lastWrapper.color = "transparent"
        }
    }

    function calDurTime() {
        if (selectMode && bar.rightStr == "x")
        {
            bar.middleStr = odvTimeList.calDurTime(index1, index2)
        }
    }

    Component {
        id: tableTimeListViewDelegate
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
                    if (selectMode)
                    {
                        if (wrapperText.text.charAt(2) == ':' &&
                                wrapperText.text.charAt(5) == '-' &&
                                wrapperText.text.charAt(8) == ':' &&
                                wrapperText.text.charAt(11) == '(' )
                        {
                            tableTimeListView.currentIndex = index
                            bar.rightStr = "x"
                        }
                        index2 = index
                        calDurTime()
                    }
                    else
                    {
                        tableTimeListView.currentIndex = index
                        bar.rightStr = ""
                        wrapperText.color = "black"
                    }
                }
                onDoubleClicked: {
                    if (!selectMode &&
                            wrapperText.text.charAt(2) == ':' &&
                            wrapperText.text.charAt(5) == '-' &&
                            wrapperText.text.charAt(8) == ':' &&
                            wrapperText.text.charAt(11) == '(' )
                    {
                        wrapper.color = "lightyellow"
                        selectMode = true
                        bar.rightStr = "x"
                        bar.rightColor = "blue"
                        index1 = index
                        lastWrapper = wrapper
                        calDurTime()
                    }
                }
                onPressAndHold: {
                    if (!selectMode && wrapperText.text.charAt(2) == ':' &&
                            wrapperText.text.charAt(5) == '-' &&
                            wrapperText.text.charAt(8) == ':' &&
                            wrapperText.text.charAt(11) == '(' )
                    {
                        tableTimeListView.currentIndex = index
                        wrapperText.color = "red"
                        bar.rightStr = "Del"
                    }
                    else
                    {
                        bar.rightStr = ""
                    }
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
                },
                State {
                    name: "Pop"
                    when: odvTimeList.isPop(index)
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        font.underline: false
                        color: "red"
                    }
                },
                State {
                    name: "BaseDur"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        font.underline: false
                        color: "black"
                    }
                },
                State {
                    name: "DelReady"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        font.underline: false
                        color: "black"
                    }
                }
            ]
        }
    }

    ListView {
        id: tableTimeListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        model: odvTimeList.curList
        delegate: tableTimeListViewDelegate
    }
    // turn day Button
    Row {
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        // Prev day Button
        ODBox.TextButtonNoDouble {
            width: parent.width / 2
            height: parent.height
            anchors.left: parent.left

            textBKColor: "lightgreen"
            textAlwayEnabled: true

            onTextClicked: {
                if (odvTimeList.prevDay())
                {
                    updateCurList()
                }
            }
            onTextLongPress: {
                if (odvTimeList.firstDay())
                {
                    updateCurList()
                }
            }
        }
        // Next day Button
        ODBox.TextButtonNoDouble {
            width: parent.width / 2
            height: parent.height
            anchors.right: parent.right

            textBKColor: "lightblue"
            textAlwayEnabled: true

            onTextClicked: {
                if (odvTimeList.nextDay())
                {
                    updateCurList()
                }
            }
            onTextLongPress: {
                if (odvTimeList.lastDay())
                {
                    updateCurList()
                }
            }
        }
    }
}
