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

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinAddTransit")
            {
                console.log("goblin add transit")
                if (bar.rightStr == "+" &&
                        odvGoblinList.addTransit(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second,
                                                 dateTime.customTime, goldFrom.currentText, goldTo.currentText, count.value, tips.value, content.text,
                                                 offsetCount.value, lessCount.value))
                {
                    tips.value = 0
                    count.value = 0
                    content.text = ""
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

        ComboBox {
            id: transitType
            width: parent.width
            height: 60
            model: ["Normal", "RepayBill"]
        }

        Row {
            width: parent.width
            height: 60
            spacing: 10

            ComboBox {
                id: goldFrom
                width: parent.width / 2 - 40
                height: parent.height
                model: odvGoblinList.getGoldFromList()
            }

            ODBox.TextButton {
                height: parent.height
                width: 50

                textStr: "<->"
                textSize: 14

                onTextClicked: {
                    var tmpIndex = goldFrom.currentIndex
                    goldFrom.currentIndex = goldTo.currentIndex
                    goldTo.currentIndex = tmpIndex
                }
            }
            ComboBox {
                id: goldTo
                width: parent.width / 2 - 40
                height: parent.height
                model: odvGoblinList.getGoldFromList()
            }
        }
        Row {
            width: parent.width
            height: 80
            spacing: 10

            Column {
                width: parent.width / 2 - 10
                height: parent.height
                Text {
                    width: parent.width
                    height: 20

                    text: "Tips:"
                }
                SpinBox {
                    id: tips
                    width: parent.width
                    height: 60

                    decimals: 2
                    minimumValue: 0
                    maximumValue: 2147483648
                }
            }
            Column {
                width: parent.width / 2 - 10
                height: parent.height

                Text {
                    width: parent.width
                    height: 20

                    text: "Count:"
                }
                SpinBox {
                    id: count
                    width: parent.width
                    height: 60

                    decimals: 2
                    minimumValue: 0
                    maximumValue: 2147483648
                }
            }
        }
        Rectangle {
            width: parent.width
            height: 60
            border.color: "black"
            TextEdit {
                id: content
                anchors.fill: parent
            }
        }
        Row {
            width: parent.width
            height: 80
            spacing: 10

            Column {
                width: parent.width / 2 - 10
                height: parent.height
                Text {
                    width: parent.width
                    height: 20

                    text: "Offset:"
                }
                SpinBox {
                    id: offsetCount
                    width: parent.width
                    height: 60

                    minimumValue: -100000
                    maximumValue: 100000
                }
            }
            Column {
                width: parent.width / 2 - 10
                height: parent.height

                Text {
                    width: parent.width
                    height: 20

                    text: "Less:"
                }
                SpinBox {
                    id: lessCount
                    width: parent.width
                    height: 60

                    decimals: 2
                    minimumValue: 0
                    maximumValue: 2147483648
                }
            }
        }
    }

}
