//====================================================================
//  GCombo.qml
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

import QtQuick 2.0
FocusScope {
    id: comboBox
    property int maxHeight: 1000
    property int listWidth: 0
    property alias currentIndex: listView.currentIndex
    property alias buttonTextSize: comboBoxButton.textSize
    property alias text: comboBoxButton.text
    property bool readOnly: false
    property int listModelSize
    property variant listModel
    property int beforeDropIndex:0
    property string stableText: ""
    property color textColor: "black"
    property color borderColor: "transparent"
    property color backgroundColor: "transparent"
    property color focus_borderColor: "transparent"
    property color focus_backgroundColor: "transparent"
    property color focus_textColor: "black"
    signal comboBoxSelected(int idx)
    signal comboBoxTextChanged(string comboxtext)
    width: 160; height: 32
    z: listBackground.height===0 ? 0 : 100

    GComboButton {
        id: comboBoxButton
        anchors.fill: parent;
        text: stableText == ""?listModel[comboBox.currentIndex]:stableText
        textSize: parent.height-4
        textColor: comboBox.activeFocus ? comboBox.focus_textColor : comboBox.textColor
        borderColor: comboBox.activeFocus ?  f.focus_borderColor : comboBox.borderColor
        backgroundColor: comboBox.activeFocus ? comboBox.focus_backgroundColor : comboBox.backgroundColor
        onClicked: comboxClick()
    }
    Component {
        id: comboBoxDelegate
        Item {
            id:comitem
            width: parent.width; height: comboBoxButton.height;
            Text {
                id:comtext
                color: index == listView.currentIndex ? "#ffff00" : "white"
                anchors.centerIn: parent
                font{pixelSize: comboBoxButton.textSize-5; bold: true;}
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: comboBox.comboxSelect(index);
            }
        }
    }

    Rectangle {
        id: listBackground
        anchors{top: comboBoxButton.bottom; right: comboBoxButton.right;}
        width: Math.max(parent.width, listWidth)
        color: "#FF000000"
        radius: comboBoxButton.radius
        border{width: comboBoxButton.borderWidth; color: comboBoxButton.borderColor;}
        ListView {
            id: listView
            anchors.fill: parent
            clip: true
            focus:true
            model:listModel
            delegate: comboBoxDelegate
            highlight: Rectangle{color:"#FF00688A"; radius: 5;}
        }

        Behavior on height {
            NumberAnimation {property: "height"; duration: 200 }
        }
    }

    function comboxSelect(index){
        currentIndex = index
        state = "Close"
    }
    function comboxClick(){
        if(readOnly) return
        forceActiveFocus()
        if (state == "Close"){
            state = "Drop"
        }
        else{
            state = "Close"
        }
    }
    onActiveFocusChanged: { if(!activeFocus) state = "Close" }
    state: "Close"
    states: [
        State {
            name: "Close"
            PropertyChanges {target: listBackground; height: 0}
            StateChangeScript{
                script: {
                    if(currentIndex===beforeDropIndex)
                        return
                    comboBoxSelected(currentIndex)
                    comboBoxTextChanged(text)
                }
            }
        },
        State {
            name: "Drop"
            PropertyChanges {target: listBackground; height: Math.min(maxHeight, listModelSize * comboBoxButton.height); focus: true}
            StateChangeScript{
                script: {
                    beforeDropIndex = currentIndex
                }
            }
        }
    ]


    Keys.onUpPressed: {
        if(state == "Drop"){ listView.decrementCurrentIndex(); return}
        event.accepted = false
    }
    Keys.onDownPressed: {
        if(state == "Drop"){ listView.incrementCurrentIndex(); return}
        event.accepted = false
    }
    Keys.onReturnPressed: {
        if(typeof(delegatelistview.model) == "undefined")
        {
            comboxClick();
            return}
        listView.focus=false;
        delegatelistview.forceActiveFocus();
        event.accepted = false
    }
    Keys.onEnterPressed: {
        if(typeof(delegatelistview.model) == "undefined")
        {
            comboxClick();
            return}
        listView.focus=false;
        delegatelistview.forceActiveFocus();
        event.accepted = false}
    Keys.onRightPressed: {if(typeof(delegatelistview.model) == "undefined")return;listView.focus=false;delegatelistview.forceActiveFocus();event.accepted = false}
    Keys.onLeftPressed: {if(delegatelistview.focus)listView.forceActiveFocus();event.accepted = false;}
    Keys.onPressed: {
        if(event.key === Qt.Key_Escape){
            if(state !== "Close"){
                state = "Close"
                event.accepted = true
            }
        }
    }
}
