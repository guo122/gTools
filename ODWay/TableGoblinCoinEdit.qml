//====================================================================
//  TableGoblinCoinEdit.qml
//  created 6.14.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Controls 1.4
import ODVGoblin 1.0
import "./ODBox" as ODBox

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    ODVGoblinList { id: vvGoblinList }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinCoinEdit" && bar.rightStr == "Save")
            {
                // save coin edit
                if (vvGoblinList.saveEditCoin(
                            revokeCheckBox.checkedState,
                            dateTime.year,
                            dateTime.month,
                            dateTime.day,
                            dateTime.hour,
                            dateTime.minute,
                            dateTime.second,
                            revokeSpinBox.value,
                            rebackGoldFrom.currentText,
                            offsetSpinBox.value))
                {
                    console.log("save success")
                    bar.back()
                }
            }
            else if (bar.barHandle == "handleTableGoblinCoinEdit" && bar.rightStr == "Del")
            {
                // save coin edit
                if (vvGoblinList.delCoin())
                {
                    console.log("del success")
                    bar.back()
                }
            }
        }
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = "Coin"
        bar.rightStr = "Save"
        bar.rightColor = "red"
        bar.barHandle = "handleTableGoblinCoinEdit"

        vvGoblinList.updateEditCoin()
        coinEditText.text = vvGoblinList.getEditCoinStrText()
        revokeCheckBox.checked = vvGoblinList.getEditCoinStrRevoke()
        revokeSpinBox.value = vvGoblinList.getEditCoinStrCountSecond()
        dateTime.isCustom = revokeCheckBox.checkedState
        dateTime.setYear = vvGoblinList.getEditCoinStrYear()
        dateTime.setMonth = vvGoblinList.getEditCoinStrMonth()
        dateTime.setDay = vvGoblinList.getEditCoinStrDay()
        dateTime.setHour = vvGoblinList.getEditCoinStrHour()
        dateTime.setMinute = vvGoblinList.getEditCoinStrMinute()
        dateTime.setSecond = vvGoblinList.getEditCoinStrSecond()
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 10

        Text {
            id:  coinEditText
        }

        CheckBox {
            id: revokeCheckBox
            checked: false

            onCheckedChanged: {
                dateTime.boxVisiable = checked
                revokeSpinBox.boxVisiable = checked
                fastSecondButton.visible = checked
                rebackGoldFrom.visible = checked
                offsetSpinBox.visible = checked
            }
        }

        ODBox.DateTimePicker{
            id: dateTime
            width: parent.width

            boxVisiable: false
        }

        ODBox.RowSpinBox {
            id: revokeSpinBox
            width: parent.width
            height: 60

            boxDecimals: 2

            preText: "Revoke: "
            boxVisiable: false
        }

        Rectangle {
            id: fastSecondButton
            width: parent.width
            height: 80
            color: "transparent"
            visible: false
            Rectangle {
                width: 100
                height: parent.height
                anchors.right: parent.right
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    width: 38
                    height: 31
                    anchors.verticalCenterOffset: -1
                    onClicked: {
                        bar.rightStr = "Save"
                        bar.rightColor = "red"
                    }
                    onDoubleClicked: {
                        bar.rightStr = "Save"
                        bar.rightColor = "red"
                        revokeSpinBox.value = vvGoblinList.getEditCoinStrCount()
                        console.log(vvGoblinList.getEditCoinStrCount())
                    }
                    onPressAndHold: {
                        bar.rightStr = "Del"
                        bar.rightColor = "red"
                    }

                    Rectangle {
                        anchors.fill: parent
                        opacity: parent.pressed ? 1 : 0
                        Behavior on opacity { NumberAnimation{ duration: 100 }}
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: "#22000000" }
                            GradientStop { position: 0.2 ; color: "#11000000" }
                        }
                        border.color: "darkgray"
                        antialiasing: true
                        radius: 4
                    }
                }
            }
        }
        Row{
            width: parent.width
            height: 60
            spacing: 10

            SpinBox {
                id: offsetSpinBox
                width: parent.width / 2 - 10
                height: 60
                visible: false

//                anchors.left: parent.left
//                anchors.leftMargin: 10
            }

            ComboBox {
                id: rebackGoldFrom
                width: parent.width / 2 - 10
                height: 60
                visible: false

//                anchors.right: parent.right
//                anchors.rightMargin: 10

                model: vvGoblinList.getGoldFromList()
            }
        }

    }
}
