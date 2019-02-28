//====================================================================
//  OriComplexComboBox.qml
//  created 2.20.19
//  written by SadVSSmile
//
//  https://blog.csdn.net/u010655288/article/details/71686712
//====================================================================

import QtQuick 2.0
FocusScope {
    id: comboBox
    property int maxHeight: 1000
    property alias currentIndex: listView.currentIndex
    property alias currentIndex2: delegatelistview.currentIndex
    property alias buttonTextSize: comboBoxButton.textSize
    property alias text: comboBoxButton.text
    property bool readOnly: false
    property variant listModel
    property int beforeDropIndex:0
    property int beforeDropIndex2: 0
    property color textColor: "white"
    property color borderColor: "olivedrab"
    property color backgroundColor: "#FF00688A"
    property color focus_borderColor: "lightsalmon"
    property color focus_backgroundColor: "#FF00688A"
    property color focus_textColor: "darkred"
    signal comboBoxSelected(int idx,int index)
    signal comboBoxTextChanged(string comboxtext)
    width: 160; height: 32
    z: listBackground.height===0 ? 0 : 100

    GComboButton {
        id: comboBoxButton
        anchors.fill: parent;
        source: "ico/down.png"
        text: typeof(listModel) == "undefined"? "":typeof( listModel.get(currentIndex).attributes)=="undefined"?listModel.get(comboBox.currentIndex).name:listModel.get(currentIndex).attributes.get(currentIndex2).description
        textSize: parent.height-4
        textColor: comboBox.activeFocus ? comboBox.focus_textColor : comboBox.textColor
        borderColor: comboBox.activeFocus ? comboBox.focus_borderColor : comboBox.borderColor
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
                text:name          }
            Text{
                id:icotext
                color:"white"
                text:typeof(listModel.get(index).attributes) == "undefined"?"":"?";
                font{pixelSize: comboBoxButton.textSize-5; bold: true;}
                anchors{top:parent.top;right: parent.right}
                verticalAlignment: TextInput.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: comboBox.comboxSelect(index);
            }
            onFocusChanged: {delegatelistview.visible=true;}
        }


    }
    Component {
        id: delegate
        Item {
            width: parent.width; height: comboBoxButton.height;
            Text {
                id:comtext
                color:"white"
                anchors.centerIn: parent
                font{pixelSize: comboBoxButton.textSize-5; bold: true;}
                text:description;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: comboBox.comboxSelect2(index);
            }
            onFocusChanged: {delegatelistview.visible=true;}
            Keys.onPressed:
            {
                if(event.key===Qt.Key_Enter||event.key===Qt.Key_Return)
                {
                    comboBox.comboxClick();
                }
            }

        }

    }

    Rectangle{
        id:delegateback
        x:listView.x+listView.width
        y:listBackground.y+listView.currentIndex*listView.highlightItem.height
        color:"#FF000000"
        radius: comboBoxButton.radius
        visible: false
        border{width: comboBoxButton.borderWidth; color: comboBoxButton.borderColor;}
        ListView
        {
            id:delegatelistview
            anchors.fill: parent
            visible:false
            clip:true
            delegate: delegate
            keyNavigationWraps :true
            highlight: Rectangle{color: delegatelistview.focus?"#FF00688A":"transparent"; radius: 5;}
        }
        Behavior on height {
            NumberAnimation {property: "height"; duration: 200 }
        }
        state: "Hide"
        states: [
            State {
                name: "Hide"
                PropertyChanges {target: delegateback; visible:false;height:0;width:0}
                StateChangeScript{
                    script: {
                        delegatelistview.focus=false
                    }
                }
            },
            State {
                name: "Show"
                PropertyChanges {target: delegateback;visible:typeof(delegatelistview.model) == "undefined"?false:true; focus: false;height: Math.min(maxHeight, typeof(delegatelistview.model) == "undefined"?0:delegatelistview.model.count*comboBoxButton.height);width:comboBoxButton.width}
                StateChangeScript{
                    script: {
                    }
                }
            }
        ]
    }
    ListModel{id:model}
    Rectangle {
        id: listBackground
        anchors{top: comboBoxButton.bottom; left: comboBoxButton.left;}
        width: parent.width
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
            onCurrentIndexChanged: {delegatelistview.model=listModel.get(currentIndex).attributes;}
        }

        Behavior on height {
            NumberAnimation {property: "height"; duration: 200 }
        }
    }
    function comboxSelect2(index)
    {
        currentIndex2=index
        console.log(index)
        state="Close"
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
            delegatelistview.model=listModel.get(currentIndex).attributes
        }
        else{
            state = "Close"
            delegateback.state="Hide"
        }
    }
    onActiveFocusChanged: { if(!activeFocus) state = "Close" }
    onStateChanged: {if(state=="Close")delegateback.state="Hide"}
    state: "Close"
    states: [
        State {
            name: "Close"
            PropertyChanges {target: listBackground; height: 0}
            StateChangeScript{
                script: {
                    if(currentIndex===beforeDropIndex && currentIndex2===beforeDropIndex2)
                        return
                    comboBoxSelected(currentIndex,currentIndex2)
                    comboBoxTextChanged(text)
                    delegateback.state="Hide"
                }
            }
        },
        State {
            name: "Drop"
            PropertyChanges {target: listBackground; height: Math.min(maxHeight, listModel.count*comboBoxButton.height); focus: true}
            StateChangeScript{
                script: {
                    beforeDropIndex = currentIndex
                    beforeDropIndex2=currentIndex2
                    delegateback.state="Show"
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
