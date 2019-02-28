//====================================================================
//  GTRandomListAdd.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4
import GTVRandomList 1.0

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    GTVRandomListQML { id: gtvRandomList }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = ""
        bar.rightStr = "+"
        bar.rightColor = "black"
        bar.middleModel = gtvRandomList.getKindList()
        bar.middleModelSize = gtvRandomList.getKindSize()
        bar.rightModelSize = 0
        bar.barHandle = "handleTableRandomListAdd"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableRandomListAdd" && bar.rightStr == "+")
            {
                if (newKindCheck.checkedState) {
                    // newKind
                    if (gtvRandomList.addData(textEditName.text, textEditKind.text))
                    {
                        textEditName.text = ""
                    }
                } else {
                    if (gtvRandomList.addData(textEditName.text, bar.middleComboText))
                    {
                        textEditName.text = ""
                    }
                }


            }
        }
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        Row {
            width: parent.width
            spacing: 10

            Text {
                id: labelText
                font.bold: true
                text: "Kind"
            }

            CheckBox {
                id: newKindCheck

                onClicked: {
                    textEditKind.visible = newKindCheck.checkedState
                    textEditKindLine.visible = newKindCheck.checkedState
                    if (newKindCheck.checkedState) {
                        bar.middleModelSize = 0
                    }
                    else {
                        bar.middleModel = gtvRandomList.getKindList()
                        bar.middleModelSize = gtvRandomList.getKindSize()
                    }
                }
            }
        }

        TextEdit {
            id: textEditKind
            width: parent.width
            height: labelText.height * 1.7
            visible: false

            font.pixelSize: labelText.font.pixelSize * 1.7
        }

        Rectangle {
            id: textEditKindLine
            width: parent.width
            height: 1
            visible: false
            color: "black"
        }

        Rectangle {
            width: parent.width
            height: 5
            color: "transparent"
        }

        Text {
            font.bold: true
            text: "Name"
        }
        TextEdit {
            id: textEditName
            width: parent.width
            height: labelText.height * 1.7
            font.pixelSize: labelText.font.pixelSize * 1.7
        }
        Rectangle {
            width: parent.width
            height: 1
            color: "black"
        }

    }

}
