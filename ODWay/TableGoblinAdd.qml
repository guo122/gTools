//====================================================================
//  TableGoblinAdd.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1

Rectangle {
    function updateList(){
        tableGoblinAddList.currentIndex = 1
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: tableGoblinAddList
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Vertical
            boundsBehavior: Flickable.StopAtBounds
            currentIndex: 1
            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    bar.leftStr = "<"
                    bar.middleStr = "Transit"
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableGoblinAddTransit"
                    tableGoblinAddTransitObject.dateTime = tableGoblinAddBasicObject.varDateTime
                }
                else if (currentIndex == 1)
                {
                    bar.leftStr = "<"
                    bar.middleStr = "Add"
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableGoblinAddBasic"
                }
                else if (currentIndex == 2)
                {
                    bar.leftStr = "<"
                    bar.middleStr = "Bill"
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableGoblinAddBill"
                    tableGoblinAddBillObject.dateTime = tableGoblinAddBasicObject.varDateTime
                    tableGoblinAddBillObject.classify = tableGoblinAddBasicObject.varClassify
                    tableGoblinAddBillObject.kindFirst = tableGoblinAddBasicObject.varKindFirst
                    tableGoblinAddBillObject.kindSecond = tableGoblinAddBasicObject.varKindSecond
                    tableGoblinAddBillObject.goldFrom = tableGoblinAddBasicObject.varGoldFrom
                    tableGoblinAddBillObject.goldCount = tableGoblinAddBasicObject.varCount
                }
            }

            model: ObjectModel {
                TableGoblinAddTransit {
                    id: tableGoblinAddTransitObject
                    height: tableGoblinAddList.height
                    width: tableGoblinAddList.width
                }
                TableGoblinAddBasic {
                    id: tableGoblinAddBasicObject
                    height: tableGoblinAddList.height
                    width: tableGoblinAddList.width
                }

                TableGoblinAddBill {
                    id: tableGoblinAddBillObject
                    height: tableGoblinAddList.height
                    width: tableGoblinAddList.width
                }
            }
        }
    }

}
