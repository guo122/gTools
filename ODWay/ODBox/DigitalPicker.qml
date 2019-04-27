//====================================================================
//  DigitalPicker.qml
//  created 6.6.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {
    property bool isOpen: false
    property bool noEcho: false
    property string theKey: "1243"
    property string numList

    height: parent.height
    width: parent.width
    color: "transparent"

    Component.onCompleted: {
        isOpen = theKey == ""
    }

    function addNum(num) {
        numList += num
        if (numList == theKey)
        {
            isOpen = true
        }
    }

    Column {
        anchors.fill: parent
        visible: !isOpen
        Row {
            width: parent.width
            height: parent.height / 3

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "7"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("7")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "8"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("8")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "9"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("9")
                }
            }
        }
        Row {
            width: parent.width
            height: parent.height / 3

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "4"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("4")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "5"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("5")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "6"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("6")
                }
            }
        }
        Row {
            width: parent.width
            height: parent.height / 3

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "1"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("1")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "2"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("2")
                }
            }

            TextButtonNoDouble {
                width: parent.width / 3
                height: parent.height

                textVisible: !noEcho
                textStr: "3"
                textSize: Math.min(parent.height, parent.width / 3)
                textBold: false

                onTextClicked: {
                    addNum("3")
                }
            }
        }
    }
}
