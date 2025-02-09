import QtQuick
import QtQuick.Controls
import "widgets"

Item {
    id: videoPlayer

    ButtonBack {
        id: buttonBack
        x: 0.05 * parent.width
        y: 0.12 * parent.height
        onClicked: ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }

    ButtonRoundBlueGradient {
        anchors.right: parent.right
        anchors.verticalCenter: buttonBack.verticalCenter
        text: "Add movies"
        sIconName: "plus.png"
        //onClicked: videoPlayerFileDialog.open()
    }
}
