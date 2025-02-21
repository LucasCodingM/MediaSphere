import QtQuick
import "widgets"
import "../.."

Window {
    id: mainWindow
    minimumWidth: 1024
    minimumHeight: 600
    visibility: ResourcesComponents.getWindowVisibility()
    visible: true
    title: qsTr("RaspGui")

    Background {}

    Header {
        id: header
    }

    Loader {
        id: loader
        anchors.fill: parent
        onSourceComponentChanged: {
            header.setMenuHeader(ResourcesComponents.currentWindowName)
        }
    }

    Component.onCompleted: {
        ResourcesComponents.setLoader(loader)
        ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }
}
