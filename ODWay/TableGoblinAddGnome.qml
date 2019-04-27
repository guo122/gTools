//====================================================================
//  TableGoblinAddGnome.qml
//  created 6.13.18
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
            if (bar.barHandle == "handleTableGoblinAddGnome" && bar.rightStr == "Add")
            {
                // add Gnome
                if (vvGoblinList.addGnome(
                            gnomeName.text,
                            gnomeCreditLimits.value,
                            gnomeBillDates.value,
                            gnomeDueDay.value,
                            gnomeTypeComboBox.currentIndex,
                            gnomeStateComboBox.currentIndex))
                {
                    bar.back()
                }
            }
        }
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = "Gnome"
        bar.rightStr = "Add"
        bar.rightColor = "red"
        bar.barHandle = "handleTableGoblinAddGnome"
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 10

        Rectangle {
            width: parent.width
            height: 60
            TextEdit{
                id: gnomeName
                anchors.fill: parent
            }
        }
        ODBox.RowSpinBox {
            id: gnomeCreditLimits
            width: parent.width
            height: 60

            preText: "CreditLimits: "
        }
        ODBox.RowSpinBox {
            id: gnomeBillDates
            width: parent.width
            height: 60

            min: 1
            max: 31

            preText: "BillDates: "
        }
        ODBox.RowSpinBox {
            id: gnomeDueDay
            width: parent.width
            height: 60

            min: 1
            max: 31

            preText: "DueDay: "
        }
        Row {
            width: parent.width
            height: 60
            spacing: 10
            ComboBox {
                id: gnomeTypeComboBox
                width: parent.width / 2 - 10
                height: parent.height

                model: ["USD", "RMB", "JPY", "EUR", "GBP", "RUPEE", "REAL", "HWAN", "RUBLE", "AUD", "TWD", "HKD"]
            }
            ComboBox {
                id: gnomeStateComboBox
                width: parent.width / 2 - 10
                height: parent.height

                model: ["Normal", "Hidden"]
            }
        }
    }
}
