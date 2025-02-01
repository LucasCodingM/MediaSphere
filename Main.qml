import QtQuick

Window {
    id: mainWindow
    minimumWidth: 1024
    minimumHeight: 600
    //visibility: Window.FullScreen
    visible: true
    title: qsTr("RaspGui")

    Background {}

    Header {}

    Loader {
        id: loader
        anchors.fill: parent
    }

    Component.onCompleted: {
        ResourcesComponents.setLoader(loader)
        ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }
}
