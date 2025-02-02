import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent

    ButtonBack {
        x: 0.05 * parent.width
        y: 0.17 * parent.height
        onClicked: ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }

    Component.onCompleted: {
        if (!openMeteoApi.getIsDataAvailable())
            openMeteoApi.fetchWeather()
    }

    // Listen for the signal from C++
    Connections {
        target: openMeteoApi // The object exposed to QML

        function onRequestFinished() {
            console.warn("requete reçue")
        }
    }
}
