//====================================================================
//  CKKPicker.qml
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4
import ODVCKK 1.0

Rectangle {
    property var ckkList
    property int basicSpacing: 10
    property alias classify: ckkClassify.classText
    property alias kindFirst: ckkKindFirst.classText
    property alias kindSecond: ckkKindSecond.classText
    color: "transparent"

    VCKK { id: vckk }

    Component.onCompleted: {
        vckk.setCKK(ckkList)
        ckkClassify.classList = vckk.classifyList()
        ckkKindFirst.classList = vckk.kindFirstList(ckkClassify.classComboText)
        ckkKindSecond.classList = vckk.kindSecondList(ckkClassify.classComboText, ckkKindFirst.classComboText)
    }

    Column {
        anchors.fill: parent
        spacing: basicSpacing

        ClassifyPicker {
            id: ckkClassify
            width: parent.width
            height: parent.height / 3 - basicSpacing
            onClassChanged: {
                ckkKindFirst.classList = vckk.kindFirstList(ckkClassify.classComboText)
                ckkKindFirst.syncCombo()
                ckkKindSecond.classList = vckk.kindSecondList(ckkClassify.classComboText, ckkKindFirst.classComboText)
                ckkKindSecond.syncCombo()
            }
        }
        ClassifyPicker {
            id: ckkKindFirst
            width: parent.width
            height: parent.height / 3 - basicSpacing
            onClassChanged: {
                ckkKindSecond.classList = vckk.kindSecondList(ckkClassify.classComboText, ckkKindFirst.classComboText)
                ckkKindSecond.syncCombo()
            }
        }
        ClassifyPicker {
            id: ckkKindSecond
            width: parent.width
            height: parent.height / 3 - basicSpacing
        }
    }
}
