//====================================================================
//  DateTimePicker.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4

Column {
    property bool boxVisiable: true
    property alias year: spinBoxYear.value
    property alias month: spinBoxMonth.value
    property alias day: spinBoxDay.value
    property alias hour: spinBoxHour.value
    property alias minute: spinBoxMinute.value
    property alias second: spinBoxSecond.value
    property alias customTime: checkBox.checkedState

    property bool isCustom: false
    property int setYear
    property int setMonth
    property int setDay
    property int setHour
    property int setMinute
    property int setSecond

    Component.onCompleted: {
        var d = new Date()
        spinBoxYear.value = d.getFullYear()
        spinBoxMonth.value = d.getMonth() + 1
        spinBoxDay.value = d.getDate()
        spinBoxHour.value = d.getHours()
        spinBoxMinute.value = d.getMinutes()
        spinBoxSecond.value = d.getSeconds()

        if (isCustom)
        {
            spinBoxYear.value = setYear
            spinBoxMonth.value = setMonth
            spinBoxDay.value = setDay
            spinBoxHour.value = setHour
            spinBoxMinute.value = setMinute
            spinBoxSecond.value = setSecond
        }
    }

    function clearCheck() {
        checkBox.checked = false
    }

    visible: boxVisiable

    Row {
        width: parent.width
        height: 50

        SpinBox {
            id: spinBoxYear
            width: parent.width / 3
            height: parent.height
            minimumValue: 1970
            maximumValue: 2038
        }
        SpinBox {
            id: spinBoxMonth
            width: parent.width / 3
            height: parent.height
            minimumValue: 1
            maximumValue: 12
        }
        SpinBox {
            id: spinBoxDay
            width: parent.width / 3
            height: parent.height
            minimumValue: 1
            maximumValue: 31
        }
    }

    Row {
        width: parent.width
        height: 50

        SpinBox {
            id: spinBoxHour
            width: parent.width / 4
            height: parent.height
            minimumValue: 0
            maximumValue: 23
        }
        SpinBox {
            id: spinBoxMinute
            width: parent.width / 4
            height: parent.height
            minimumValue: 0
            maximumValue: 60
        }
        SpinBox {
            id: spinBoxSecond
            width: parent.width / 4
            height: parent.height
            minimumValue: 0
            maximumValue: 60
        }
        CheckBox {
            id: checkBox
            width: parent.width / 5
            height: parent.height
            checked: false
        }
    }
}
