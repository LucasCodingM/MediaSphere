import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent

    ButtonBack {
        x: 50
        y: 100
        onClicked: ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }
}
