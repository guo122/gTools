//====================================================================
//  TableTimeChartSum.qml
//  created 6.11.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    property bool isInit: true
    property var lastWrapper
    function updateSum() {
        isInit = true
        tableTimeChartSumListView.model = ""
        tableTimeChartSumListView.model = odvTimeList.getLastCKKSumStr()
    }

    Component {
        id: tableTimeChartSumDelegate
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
            Component.onCompleted: {
                wrapperText.color = odvTimeList.getLastCKKSumStrColor(index, "black")
                console.log(index, modelData)
                if (odvTimeList.isChartSumCurrentDay(index))
                {
                    wrapper.state = "Current"
                    lastWrapper = wrapper
                }
            }
            MouseArea {
                anchors.fill: parent

                onClicked: {
                    if (lastWrapper)
                    {
                        lastWrapper.state = "Normal"
                    }
                    isInit = false
                    tableTimeChartSumListView.currentIndex = index
                    odvTimeList.selectChartSum(index)
                }
            }
            // indent the item if it is the current item
            states: [
                State {
                    name: "Normal"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        font.underline: false
                    }
                },
                State {
                    name: "Current"
                    when: wrapper.ListView.isCurrentItem && !isInit
                    PropertyChanges {
                        target: wrapperText
                        font.bold: true
                        font.underline: true
                    }
                }
            ]
        }
    }

    ListView {
        id: tableTimeChartSumListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        delegate: tableTimeChartSumDelegate
    }
}
