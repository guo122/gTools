//====================================================================
//  LauncherList.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0

Rectangle {
    property int activePageCount: 0
    color: "transparent"

    function addExample(name, desc, url) {
        myModel.append({"name":name, "description":desc, "url":url})
    }
    function showExample(url) {
        pageComponent.createObject(pageContainer, { exampleUrl: url }).show()
    }

    // main window
    Rectangle {
        anchors.fill: parent
        color: "transparent"

        ListView {
            id: launcherList
            anchors.fill: parent
            anchors.topMargin: 30
            clip: true
            delegate: SimpleLauncherDelegate{
                onClicked: showExample(url)
            }
            model: ListModel {id:myModel}
            enabled: opacity == 1.0
        }
    }

    Item {
        id: pageContainer
        anchors.fill: parent
    }

    Component {
        id: pageComponent
        Rectangle {
            id: page
            clip: true
            property url exampleUrl
            width: parent.width
            height: parent.height
//            color: "white"
            MouseArea{
                //Eats mouse events
                anchors.fill: parent
            }
            Loader{
                focus: true
                source: parent.exampleUrl
                anchors.fill: parent
            }

            x: -width

            function show() {
                showAnim.start()
            }

            function exit() {
                exitAnim.start()
            }

            ParallelAnimation {
                id: showAnim
                ScriptAction {
                    script: activePageCount++
                }
                NumberAnimation {
                    target: launcherList
                    property: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: 200
                }
                NumberAnimation {
                    target: launcherList
                    property: "scale"
                    from: 1.0
                    to: 0.0
                    duration: 200
                }
                NumberAnimation {
                    target: page
                    property: "x"
                    from: -page.width
                    to: 0
                    duration: 100
                }
            }
            SequentialAnimation {
                id: exitAnim

                ScriptAction {
                    script: activePageCount--
                }

                ParallelAnimation {
                    NumberAnimation {
                        target: launcherList
                        property: "opacity"
                        from: 0.0
                        to: 1.0
                        duration: 100
                    }
                    NumberAnimation {
                        target: launcherList
                        property: "scale"
                        from: 0.0
                        to: 1.0
                        duration: 100
                    }
                    NumberAnimation {
                        target: page
                        property: "x"
                        from: 0
                        to: -page.width
                        duration: 100
                    }
                }

                ScriptAction {
                    script: page.destroy()
                }
            }
            onXChanged: {
                x = 0
            }
        }
    }

    Bar {
        id:bar
        anchors.top: parent.top
    }
}
