//====================================================================
//  TableGoblinAdd.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4
import "./ODBox" as ODBox

Rectangle {
    property var dateTime
    property string classify
    property string kindFirst
    property string kindSecond
    property string goldFrom
    property double goldCount

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinAddBill")
            {
                if (bar.rightStr == "+" &&
                        odvGoblinList.addBill(
                            dateTime.year, dateTime.month, dateTime.day,
                            dateTime.hour, dateTime.minute, dateTime.second, dateTime.customTime,
                            goldFrom, classify, kindFirst, kindSecond, goldCount,
                            monthSpinBox.value, firstMonthSpinBox.value, othersMonthSpinBox.value, content.text,
                            billSplitCheckBox.checkedState, withdrawCheckbox.checkedState, reverseCheckBox.checkedState,
                            withDrawGoldTo.currentText))
                {
                    console.log("addBil success")
                    content.text = ""
                    monthSpinBox.clear()
                    firstMonthSpinBox.value = 0
                    othersMonthSpinBox.clear()
                    rootTableGoblin.currentIndex = 0
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 10

        ODBox.RowSpinBox {
            id: monthSpinBox
            width: parent.width
            height: 60

            preText: "Month: "
        }

        Rectangle {
            width: parent.width
            height: 60

            Text {
                id: firstMonthText
                text: "FirstMonth"
            }
            CheckBox {
                id: reverseCheckBox
                width: 40
                height: parent.height
                anchors.right: firstMonthSpinBox.left

                checked: false
                onCheckedChanged: {
                    if (checked)
                    {
                        firstMonthText.text = "EndMonth"
                    }
                    else
                    {
                        firstMonthText.text = "FirstMonth"
                    }
                }
            }
            SpinBox {
                id: firstMonthSpinBox
                width: parent.width / 2 - 10
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: 10

                minimumValue: 0
                maximumValue: 100000000

                decimals: 2
            }
        }

        ODBox.RowSpinBox {
            id: othersMonthSpinBox
            width: parent.width
            height: 60

            boxDecimals: 2

            preText: "OthersMonth: "
        }

        Rectangle {
            width: parent.width
            height: 80
            border.color: "black"
            TextEdit {
                id: content
                anchors.fill: parent
            }
        }
        Row {
            width: parent.width
            height: 80

            Text {
                text: "billSplit: "
            }
            CheckBox {
                id: billSplitCheckBox

                checked: false
                onCheckedChanged: {
                    if (checkedState)
                    {
                        withdrawCheckbox.checked = false
                    }
                }
            }
        }
        Row {
            width: parent.width
            height: 80

            Text {
                text: "InstallWithdraw: "
            }
            CheckBox {
                id: withdrawCheckbox

                checked: false

                onCheckedChanged: {
                    if (checkedState)
                    {
                        billSplitCheckBox.checked = false
                    }
                }
            }
            ComboBox {
                id: withDrawGoldTo
                width: parent.width / 2 - 10
                height: parent.height
                model: odvGoblinList.getGoldFromList()
            }
        }
    }

}
