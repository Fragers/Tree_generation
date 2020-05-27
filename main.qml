import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3
Window {
    visible: true
    title: qsTr("LulW")
    minimumHeight: cl.height
    maximumHeight: cl.height
    width: 600


    minimumWidth: 600
    maximumWidth: 600
    height: cl.height



    ColumnLayout{
        id: cl

        Gameplay{
            id: gameplay
        }

        Toolbar{
            id: toolbar
            onQuitApp: Qt.quit()
            onNewGame: gameplay.newGame()
        }
    }
}
