//import ResourcesComponents
import QtQuick

Item {
    width: 1024
    height: 600
    //anchors.fill: parent
    id: menuPage1
    property int leftPos: 0.15 * width
    property int rightPos: 0.65 * width
    property int topPos: 0.12 * height
    property int bottomPos: 0.53 * height
    ButtonBlueGradient {
        id: buttonAudioPlayer
        x: menuPage1.leftPos
        y: menuPage1.topPos
        width: 0.2 * parent.width
        height: 0.3 * parent.height
        sPathIcone: "music"
    }
    ButtonBlueGradient {
        id: buttonWeather
        x: menuPage1.rightPos
        y: menuPage1.topPos
        width: 0.2 * parent.width
        height: 0.3 * parent.height
        sPathIcone: "weather"
        onClicked: ResourcesComponents.loadComponent("weather")
    }
    ButtonBlueGradient {
        id: buttonVideoPlayer
        x: menuPage1.leftPos
        y: menuPage1.bottomPos
        width: 0.2 * parent.width
        height: 0.3 * parent.height
        sPathIcone: "movie"
    }
    ButtonBlueGradient {
        id: buttonGames
        x: menuPage1.rightPos
        y: menuPage1.bottomPos
        width: 0.2 * parent.width
        height: 0.3 * parent.height
        sPathIcone: "games"
    }
}
