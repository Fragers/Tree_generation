import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3


RowLayout{
    signal newGame()
    signal quitApp()
    signal trac()
    //property var c: 1
    property var startTime: 120
    property var currentTime: 0
    id: rl

    function winGame(){
        timer.stop()
        time.text = "You win!!!"
        messagedialogwin.setVisible(true)
    }

    Button{
        id: newGameButton
        text: "New game"
        onClicked:{
            startTime = 120
            newGame()
        }
    }

    MessageDialog{
        id: messagedialoglose
        title: "You lose"
        text: "LOOOOSER"
        onAccepted: {
            startTime = 120
            timer.start()
            newGame()
        }
    }

    MessageDialog{
        id: messagedialogwin
        title: "Congratulation"
        text: "Was it too easy?"
        onAccepted: {
            startTime = 120
            timer.start()
            newGame()
        }
    }

    TextField{
        y: parent.height/2
        x:parent.width/2
        Layout.fillWidth: true
        id: tf

        Timer{
            id: timer
            interval: 1000; running: true; repeat: true
            onTriggered: {
                startTime = startTime - 1
                if(time.text.toString() == "0"){
                    timer.stop()
                    time.text = "You lose"
                    messagedialoglose.setVisible(true)
                }
                time.text = startTime.toString()
            }
        }


        Text {
            id: time
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
        }
    }

    Button{
        id: quitButton
        text: "Quit"
        onClicked: quitApp()

    }

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: ["Ctrl+N"]
        onActivated: newGame()
    }

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: [StandardKey.Close, "Ctrl+Q"]
        onActivated: quitApp()
    }

}
