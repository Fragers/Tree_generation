import QtQuick 2.0

Rectangle{
    height: 60
    width: 60
    color: "grey"
    border.color: "black"
    border.width: 1
    signal rotated(int config)
    property int config: value
    property bool light: false

    function rotate(){
        config = (config >>> 1)|((config & 1) << 3)
    }

    Rectangle{
        x:29; y: 1; width: 2; height: 30
        color: light ? "yellow" : "white"
        visible: (parent.config & 8) !== 0
    }

    Rectangle{
        x:1; y: 29; width: 30; height: 2

        color: light ? "yellow" : "white"
        visible: (parent.config & 4) !== 0
    }

    Rectangle{
        x:29; y: 29; width: 2; height: 30
        color: light ? "yellow" : "white"
        visible: (parent.config & 2) !== 0
    }

    Rectangle{
        x:29; y: 29; width: 30; height: 2
        color: light ? "yellow" : "white"
        visible: (parent.config & 1) !== 0
    }
    MouseArea{
        anchors.fill: parent

        onClicked:{
            rotate()
            rotated(parent.config)
        }
    }
}
