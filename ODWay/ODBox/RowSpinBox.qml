//====================================================================
//  RowSpinBox.qml
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    property bool boxVisiable: true
    property int boxDecimals: 0
    property string preText
    property int min: 0
    property int max: 214748364
    property alias value: spinBox.value

    visible: boxVisiable

    function clear()
    {
        spinBox.value = 0
    }

    Row {
        anchors.fill: parent
        spacing: 10
        Text {
            width: parent.width / 2 - 10
            height: parent.height

            text: preText
        }
        SpinBox {
            id: spinBox
            width: parent.width / 2 - 10
            height: parent.height

            decimals: boxDecimals

            minimumValue: min
            maximumValue: max
        }
    }
}
