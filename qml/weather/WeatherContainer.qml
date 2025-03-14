import QtQuick
import "../../"

Rectangle {
    id: weatherContainer
    width: 0.22 * parent.width
    height: 0.65 * parent.height
    color: "#1f3c70"
    property int iDayOfWeek: 0
    property bool itemTemperatureMinMaxVisible: sTemperature == "-"
    property string sTemperature: "-"
    property string sTemperatureMax: "-"
    property string sTemperatureMin: "-"
    property int iWeatherCode: -1
    property bool isNight: false

    // Code	Description
    // 0	Clear sky
    // 1, 2, 3	Mainly clear, partly cloudy, and overcast
    // 45, 48	Fog and depositing rime fog
    // 51, 53, 55	Drizzle: Light, moderate, and dense intensity
    // 56, 57	Freezing Drizzle: Light and dense intensity
    // 61, 63, 65	Rain: Slight, moderate and heavy intensity
    // 66, 67	Freezing Rain: Light and heavy intensity
    // 71, 73, 75	Snow fall: Slight, moderate, and heavy intensity
    // 77	Snow grains
    // 80, 81, 82	Rain showers: Slight, moderate, and violent
    // 85, 86	Snow showers slight and heavy
    // 95 *	Thunderstorm: Slight or moderate
    // 96, 99 *	Thunderstorm with slight and heavy hail
    property list<int> listWeatherOvercast: [1, 2, 3]
    property list<int> listWeatherCloudy: [45, 48, 51, 53, 55, 56, 57, 80, 81, 82]
    property list<int> listWeatherRain: [61, 63, 65, 66, 67]
    property list<int> listWeatherSnow: [71, 73, 75, 77, 85, 86]
    property list<int> listWeatherStorm: [95, 96, 99]

    function getDayOfWeek() {
        if (iDayOfWeek == 0)
            return qsTr("TODAY")
        var today = new Date()
        var dayChoosen = new Date(today)
        dayChoosen.setDate(today.getDate() + iDayOfWeek) // Add n day
        var daysOfWeek = [qsTr("Sunday"), qsTr("Monday"), qsTr("Tuesday"), qsTr(
                              "Wednesday"), qsTr("Thursday"), qsTr(
                              "Friday"), qsTr("Saturday")]
        return daysOfWeek[dayChoosen.getDay()]
    }

    function selectWeatherIcone() {
        if (iWeatherCode === 0)
            return ResourcesComponents.rootAssetsPath
                    + (isNight ? "weatherMoon.png" : "weatherSun.png")
        if (listWeatherOvercast.includes(iWeatherCode))
            return ResourcesComponents.rootAssetsPath
                    + (isNight ? "weatherOvercastNight.png" : "weatherOvercast.png")
        if (listWeatherCloudy.includes(iWeatherCode))
            return ResourcesComponents.rootAssetsPath + "weatherCloudy.png"
        if (listWeatherRain.includes(iWeatherCode))
            return ResourcesComponents.rootAssetsPath + "weatherRain.png"
        if (listWeatherSnow.includes(iWeatherCode))
            return ResourcesComponents.rootAssetsPath + "weatherSnow.png"
        if (listWeatherStorm.includes(iWeatherCode))
            return ResourcesComponents.rootAssetsPath + "weatherWind.png"
        return ""
    }

    Text {
        id: textTmr
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0.05 * parent.height
        color: "white"
        font.capitalization: Font.AllUppercase
        font.pixelSize: 0.085 * parent.height
        text: weatherContainer.getDayOfWeek()
    }

    Text {
        id: textTemperature
        visible: !weatherContainer.itemTemperatureMinMaxVisible
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0.25 * parent.height
        color: "white"
        font.capitalization: Font.AllUppercase
        font.pixelSize: 0.15 * parent.height
        text: weatherContainer.sTemperature + " °C"
    }

    Image {
        id: iconThermostat
        visible: weatherContainer.itemTemperatureMinMaxVisible
        anchors.left: parent.left
        anchors.leftMargin: 0.05 * parent.width
        anchors.top: parent.top
        anchors.topMargin: 0.2 * parent.height
        source: ResourcesComponents.rootAssetsPath + "degrees.png"
        fillMode: Image.PreserveAspectFit
        mipmap: true
        height: 0.3 * parent.height
    }

    Text {
        id: textTemperatureMin
        visible: weatherContainer.itemTemperatureMinMaxVisible
        anchors.left: textTemperatureMax.left
        anchors.bottom: iconThermostat.bottom
        color: "white"
        font.capitalization: Font.AllUppercase
        font.pixelSize: 0.085 * weatherContainer.height
        text: weatherContainer.sTemperatureMin + " °C"
    }

    Text {
        id: textTemperatureMax
        visible: weatherContainer.itemTemperatureMinMaxVisible
        anchors.left: iconThermostat.right
        anchors.leftMargin: 0.076 * parent.width
        anchors.top: iconThermostat.top
        color: "white"
        font.capitalization: Font.AllUppercase
        font.pixelSize: 0.085 * weatherContainer.height
        text: weatherContainer.sTemperatureMax + " °C"
    }

    Item {
        width: parent.width
        height: parent.height / 2
        anchors.bottom: parent.bottom
        Image {
            id: iconWeather
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: 0.8 * parent.width
            source: weatherContainer.selectWeatherIcone()
        }
    }
}
