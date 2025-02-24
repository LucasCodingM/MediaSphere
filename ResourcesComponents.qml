pragma Singleton

import QtQuick
import "qml/weather"
import "qml/shared/menu"
import "qml/videoPlayer"

Item {
    id: resourcesComponents

    property Item loader

    property string rootAssetsPath: "qrc:/qt/qml/MediaSphere/assets/"

    property int currentWindowName: -1

    property int windowVisibility: Window.AutomaticVisibility

    function getWindowVisibility() {
        return windowVisibility
    }

    function setWindowVisibility(enumWindowVisibility) {
        windowVisibility = enumWindowVisibility
    }

    function getLoader() {
        return loader
    }

    function setLoader(itemLoader) {
        loader = itemLoader
    }

    function loadComponent(choiceEnumComponent) {
        currentWindowName = choiceEnumComponent
        switch (choiceEnumComponent) {
        case Enum.WindowName.Menu:
        {
            loader.sourceComponent = menuComponent
            break
        }
        case Enum.WindowName.Weather:
        {
            loader.sourceComponent = weatherComponent
            break
        }
        case Enum.WindowName.VideoPlayer:
        {
            loader.sourceComponent = videoPlayerComponent
            break
        }
        default:
        {
            loader.sourceComponent = Item
            break
        }
        }
    }

    Component {
        id: weatherComponent
        Weather {}
    }

    Component {
        id: menuComponent
        Menu {}
    }

    Component {
        id: videoPlayerComponent
        VideoPlayer {}
    }
}
