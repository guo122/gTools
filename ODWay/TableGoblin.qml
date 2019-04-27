//====================================================================
//  TableGoblin.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import ODVGoblin 1.0

Rectangle {
    id: mainRect

    ColumnLayout {
        anchors.fill: parent

        ODVGoblinList { id: odvGoblinList }

        ListView {
            id: rootTableGoblin
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds
            currentIndex: 0

            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    bar.leftStr = "<"
                    bar.rightStr = ""
                    bar.rightColor = "black"
                    bar.middleStr = "Gnome"
                    bar.barHandle = "handleTableGoblinListGnome"
                    listView.update()
                }
                else if (currentIndex == 1)
                {
                    bar.leftStr = "<"
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.middleStr = "Add"
                    bar.barHandle = "handleTableGoblinAddBasic"
                    addView.updateList()
                }
            }

            model: ObjectModel {
                TableGoblinList {
                    id: listView
                    height: rootTableGoblin.height
                    width: rootTableGoblin.width
                }

                TableGoblinAdd {
                    id: addView
                    height: rootTableGoblin.height
                    width: rootTableGoblin.width
                }
            }
        }
    }
}
