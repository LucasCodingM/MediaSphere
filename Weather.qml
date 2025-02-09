import QtQuick
import QtQuick.Controls
import "widgets"

Item {
    id: weather
    anchors.fill: parent

    ButtonBack {
        id: buttonBack
        x: 0.05 * parent.width
        y: 0.12 * parent.height
        onClicked: ResourcesComponents.loadComponent(Enum.WindowName.Menu)
    }

    ButtonRoundBlueGradient {
        anchors.right: parent.right
        anchors.verticalCenter: buttonBack.verticalCenter
        text: "Refresh"
        sIconName: "refresh.png"
        onClicked: openMeteoApi.fetchWeather()
    }

    Component.onCompleted: {
        if (!openMeteoApi.getIsDataAvailable())
            openMeteoApi.fetchWeather()
        else
            updateWeather()
    }

    function updateWeather() {
        updateTodayWeather()
        updateTmrWeather()
        updateAfterTmrWeather()
    }

    function updateTodayWeather() {
        todayWeather.sTemperature = openMeteoApi.getCurrentWeatherData(
                    )["temperature_2m"]
        todayWeather.iWeatherCode = openMeteoApi.getCurrentWeatherData(
                    )["weather_code"]
    }

    function updateTmrWeather() {
        tmrWeather.sTemperatureMax = openMeteoApi.getListDailyWeatherData(
                    )["temperature_2m_max"][1]
        tmrWeather.sTemperatureMin = openMeteoApi.getListDailyWeatherData(
                    )["temperature_2m_min"][1]
        tmrWeather.iWeatherCode = openMeteoApi.getListDailyWeatherData(
                    )["weather_code"][1]
    }

    function updateAfterTmrWeather() {
        afterTmrWeather.sTemperatureMax = openMeteoApi.getListDailyWeatherData(
                    )["temperature_2m_max"][2]
        afterTmrWeather.sTemperatureMin = openMeteoApi.getListDailyWeatherData(
                    )["temperature_2m_min"][2]
        afterTmrWeather.iWeatherCode = openMeteoApi.getListDailyWeatherData(
                    )["weather_code"][2]
    }

    // Listen for the signal from C++
    Connections {
        target: openMeteoApi // The object exposed to QML

        function onRequestFinished() {
            if (openMeteoApi.getIsDataAvailable()) {
                updateWeather()
            }
        }
    }
    WeatherContainer {
        id: todayWeather
        y: 0.3 * parent.height
        anchors.left: parent.left
        anchors.leftMargin: 0.06 * parent.width
        iDayOfWeek: 0
    }

    WeatherContainer {
        id: tmrWeather
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: todayWeather.verticalCenter
        iDayOfWeek: 1
    }

    WeatherContainer {
        id: afterTmrWeather
        anchors.right: parent.right
        anchors.rightMargin: 0.06 * parent.width
        anchors.verticalCenter: todayWeather.verticalCenter
        iDayOfWeek: 2
    }
}
