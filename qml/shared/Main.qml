import QtQuick
import "widgets"
import "../.."

Window {
    id: mainWindow
    minimumWidth: 1024
    minimumHeight: 600
    visibility: ResourcesComponents.getWindowVisibility()
    visible: true
    title: qsTr("MediaSphere")

    Background {}

    Header {
        id: header
        visible: ResourcesComponents.getWindowVisibility() != Window.FullScreen
        z: 1
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
