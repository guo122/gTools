//====================================================================
//  TableTime.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import ODVTime 1.0

Rectangle {
    id: mainRect

    ColumnLayout {
        anchors.fill: parent

        ODVTimeList { id: odvTimeList }

        Item {
            Timer {
                interval: 500; running: true; repeat: true
                onTriggered: {
                    if (bar.barHandle == "handleTableTimeAdd" ||
                            bar.barHandle == "handleTableTimeList")
                    {
                        bar.middleStr = odvTimeList.runningTimeStr
                        listView.calDurTime()
                    }
                }
            }
        }

        ListView {
            id: rootTableTime
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds
            // todo 0 -> 2
            currentIndex: 2

            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    // chart
                    bar.leftStr = "<"
                    bar.rightStr = ""
                    bar.rightColor = "black"
                    bar.middleStr = odvTimeList.getCKKStr("Chart")
                    bar.barHandle = "handleTableTimeChart"
                    timeChart.update()
                }
                else if (currentIndex == 1)
                {
                    // add
                    bar.leftStr = "<"
                    bar.rightStr = "All"
                    bar.rightColor = "black"
                    bar.barHandle = "handleTableTimeSum"
                    timeSum.allSum = false
                    timeSum.updateSum()
                    listView.endList()
                }
                else if (currentIndex == 2)
                {
                    // list
                    bar.leftStr = "<"
                    bar.middleStr = odvTimeList.runningTimeStr
                    bar.rightStr = ""
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableTimeList"
                    listView.updateCurList()
                }
                else if (currentIndex == 3)
                {
                    // add
                    bar.leftStr = "<"
                    bar.middleStr = odvTimeList.runningTimeStr
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableTimeAdd"
                    listView.endList()
                }
            }

            model: ObjectModel {
                TableTimeChartList {
                    id: timeChart
                    height: rootTableTime.height
                    width: rootTableTime.width
                }

                TableTimeSum {
                    id: timeSum
                    height: rootTableTime.height
                    width: rootTableTime.width
                }

                TableTimeList {
                    id: listView
                    height: rootTableTime.height
                    width: rootTableTime.width
                }

                TableTimeAdd {
                    id: addView
                    height: rootTableTime.height
                    width: rootTableTime.width
                }
            }
        }
    }
}
