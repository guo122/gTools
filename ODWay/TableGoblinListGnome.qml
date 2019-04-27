//====================================================================
//  TableGoblinListGnome.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {
    id: iiTableGoblinListGnome
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
        bar.leftStr = "<"
        bar.rightStr = ""
        bar.rightColor = "black"
        bar.middleStr = "Gnome"
        bar.barHandle = "handleTableGoblinListGnome"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinListGnome" && bar.rightStr == "Add")
            {
                // open TableGoblinAddGnome
                bar.rightStr = ""
                bar.openUrl(iiTableGoblinListGnome, "TableGoblinAddGnome.qml")
            }
            else if (bar.barHandle == "handleTableGoblinListGnome" && bar.rightStr == "Up")
            {
                // open TableGoblinAddGnome
                bar.rightStr = "Coin"
                odvGoblinList.upGnome(tableGoblinListView.currentIndex)
                iiTableGoblinListGnome.update()
            }
            else if (bar.barHandle == "handleTableGoblinListGnome" && bar.rightStr == "Coin")
            {
                // open TableGoblinAddGnome
                tableGoblinList.currentIndex = 1
            }
        }
    }

    function update() {
        tableGoblinListView.model = ""
        tableGoblinListView.model = odvGoblinList.getGnomeList()
    }

    Component {
        id: tableGoblinListViewDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 55
            color: "transparent"

            Component.onCompleted: {
                if (index == 0)
                {
                    wrapper.height = 122
                }
            }

            Text {
                id: wrapperText
                width: parent.width
                font.pixelSize: 20
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tableGoblinListView.currentIndex = index
                    odvGoblinList.setGnomeIndex(index)
                    bar.rightColor = "black"
                    if (wrapperText.text == "Add")
                    {
                        bar.rightStr = "Add"
                    }
                    else
                    {
                        bar.rightStr = "Coin"
                    }
                }
                onDoubleClicked: {
                    tableGoblinListView.currentIndex = index
                    odvGoblinList.setGnomeIndex(index)
                    if (wrapperText.text != "Add" && index != 0 && index != 1)
                    {
                        bar.rightStr = "Up"
                        bar.rightColor = "red"
                    }
                    else
                    {
                        bar.rightStr = "Coin"
                        bar.rightColor = "balck"
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
                        color: "black"
                    }
                },
                State {
                    name: "Normal"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
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

