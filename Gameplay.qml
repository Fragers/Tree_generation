import QtQuick 2.14
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.12
GridLayout{
    signal wingame()
    id: gl

    width: 600
    height: 600

    columns: 10
    rows: 10

    function newGame(){
        var newGameConfigs = helper.newGame()
        for(var i = 0; i < newGameConfigs.length; i++){
            bricks.itemAt(i).config = newGameConfigs[i]
        }
        bricks.itemAt(0).light = true
    }

    function light(){
        var brickConfig = []
        for(var i =0; i < bricks.count; i++){
            brickConfig.push(bricks.itemAt(i).config)

        }
        var brickLights = helper.light(brickConfig)
        for(var i = 0; i < brickLights.length; i++){
            bricks.itemAt(i).light = brickLights[i]
        }


    }

    columnSpacing: 0
    rowSpacing: 0
    Repeater {
        id: bricks
        model: 100

        Brick{
            onRotated: {
                gl.light()
                var lightCount = helper.getLight()
                //console.log(lightCount)
                if(lightCount === 100){
                    toolbar.winGame()
                    gl.wingame()
                }
            }
        }
    }
    Component.onCompleted: {
        newGame()
        gl.light()
    }
}
