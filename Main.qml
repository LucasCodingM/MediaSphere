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

    Menu {}
}
