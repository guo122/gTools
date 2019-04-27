//====================================================================
//  TableGoblinList.qml
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1

Rectangle {
    function update(){
        tableGoblinList.currentIndex = 0
        tableGoblinListGnomeObject.update()
        tableGoblinListCoinObject.update()
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: tableGoblinList
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Vertical
            boundsBehavior: Flickable.StopAtBounds
            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    bar.leftStr = "<"
                    bar.rightStr = ""
                    bar.rightColor = "black"
                    bar.middleStr = "Gnome"
                    bar.barHandle = "handleTableGoblinListGnome"
                    tableGoblinListGnomeObject.update()
                }
                else if (currentIndex == 1)
                {
                    bar.leftStr = "<"
                    bar.rightStr = "Gnome"
                    bar.rightColor = "black"
                    bar.middleStr = odvGoblinList.getCurGnomeStr("Coin")
                    bar.barHandle = "handleTableGoblinListCoin"
                    tableGoblinListCoinObject.update()
                }
            }

            model: ObjectModel {
                TableGoblinListGnome {
                    id: tableGoblinListGnomeObject
                    height: tableGoblinList.height
                    width: tableGoblinList.width
                }
                TableGoblinListCoin {
                    id: tableGoblinListCoinObject
                    height: tableGoblinList.height
                    width: tableGoblinList.width
                }
            }
        }
    }

}
