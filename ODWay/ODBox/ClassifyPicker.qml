//====================================================================
//  ClassifyPicker.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4

Rectangle {
    property var classList
    property alias classText: textEdit.text
    property alias classComboText: comboBox.currentText
    height: parent.height
    width: parent.width
    border.color: "black"

    signal classChanged

    function syncCombo() {
        textEdit.text = comboBox.currentText
    }

    TextEdit {
        id: textEdit
        width: parent.width / 2
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Component.onCompleted: {
            textEdit.text = comboBox.currentText
        }
    }

    ComboBox {
        id: comboBox
        width: 50
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        model: classList
        onCurrentIndexChanged: {
            textEdit.text = currentText
            classChanged()
        }
    }
}
