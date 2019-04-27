//====================================================================
//  TableGoblinListCoin.qml
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {
    id: iiTableGoblinListCoin
    // 0: default; 1: durMode; 2: deleteMode
    property bool selectMode: false
    property int index1: 0
    property int index2: 0
    property var lastWrapper
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinListCoin" && bar.rightStr == "Del")
            {
                if (odvGoblinList.delCoin(tableGoblinListView.currentIndex))
                {
                    update()
                    bar.rightStr = "Gnome"
                    bar.rightColor = "black"
                }
            }
            else if (bar.barHandle == "handleTableGoblinListCoin" && bar.rightStr == "Gnome")
            {
                tableGoblinList.currentIndex = 0
            }
            else if (bar.barHandle == "handleTableGoblinListCoin" && bar.rightStr == "Edit")
            {
                if (odvGoblinList.setEditCoin(tableGoblinListView.currentIndex))
                {
                    bar.rightStr = ""
                    bar.rightColor = "black"
                    bar.openUrl(iiTableGoblinListCoin, "TableGoblinCoinEdit.qml")
                }
            }
        }
    }

    function update() {
        tableGoblinListView.model = ""
        tableGoblinListView.model = odvGoblinList.getCoinList()
    }

    Component {
        id: tableGoblinListViewDelegate
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
                    tableGoblinListView.currentIndex = index
                    wrapperText.color = "black"
                    bar.rightStr = "Gnome"
                    bar.rightColor = "black"
                }
                onDoubleClicked: {
                    tableGoblinListView.currentIndex = index
                    wrapperText.color = "red"
                    bar.rightStr = "Edit"
                    bar.rightColor = "red"
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
                    name: "Normal"
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
        id: tableGoblinListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        focus: false
        model: odvGoblinList.getGnomeList()
        delegate: tableGoblinListViewDelegate
    }

    ListModel{
        id: aaa
        ListElement{name:"Add"}
    }
}

