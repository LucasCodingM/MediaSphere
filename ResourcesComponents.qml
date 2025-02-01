pragma Singleton

import QtQuick

Item {
    id: resourcesComponents

    property Item loader

    property string rootAssetsPath: "qrc:/qt/qml/RaspGui/assets/"

    function getLoader() {
        return loader
    }

    function setLoader(itemLoader) {
        loader = itemLoader
    }

    function loadComponent(choiceEnumComponent) {
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
}
