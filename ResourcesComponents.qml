pragma Singleton

import QtQuick

Item {
    id: resourcesComponents
    width: 1024
    height: 600

    property Item loader

    property string rootAssetsPath: "qrc:/qt/qml/RaspGui/assets/"

    function getLoader() {
        return loader
    }

    function setLoader(itemLoader) {
        loader = itemLoader
    }

    function loadComponent(sComponentName) {
        if (sComponentName == "menu")
            loader.sourceComponent = menuComponent
        if (sComponentName == "weather")
            loader.sourceComponent = weatherComponent
        return Item
    }

    Component {
        id: weatherComponent
        Weather {}
    }

    Component {
        id: menuComponent
        Menu {}
    }
}
