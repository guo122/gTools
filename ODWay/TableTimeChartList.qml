//====================================================================
//  TableTimeChartList.qml
//  created 6.11.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1

Rectangle {

    function update(){
        tableTimeChartObject.update()
        tableTimeChartList.currentIndex = 0
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: tableTimeChartList
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Vertical
            boundsBehavior: Flickable.StopAtBounds
            onCurrentIndexChanged: {
                if (currentIndex == 1)
                {
                    // chart
                    tableTimeChartSumObject.updateSum()
                }
            }

            model: ObjectModel {
                TableTimeChart {
                    id: tableTimeChartObject
                    height: tableTimeChartList.height
                    width: tableTimeChartList.width
                }

                TableTimeChartSum {
                    id: tableTimeChartSumObject
                    height: tableTimeChartList.height
                    width: tableTimeChartList.width
                }
            }
        }
    }
}
