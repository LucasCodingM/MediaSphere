import QtQuick
import "../.."

Rectangle {
    id: header
    width: parent.width
    height: 0.08 * parent.height

    property string mainMenu: qsTr("MAIN MENU")
    property string audioPlayerMenu: qsTr("AUDIO PLAYER")
    property string parameterMenu: qsTr("PARAMETER")
    property string videoPlayerMenu: qsTr("VIDEO PLAYER")
    property string weatherMenu: qsTr("WEATHER")
    property string gamesMenu: qsTr("GAMES")

    property string mainMenuIcone: "mainMenu.png"
    property string audioPlayerMenuIcone: "music.png"
    property string parameterMenuIcone: "parameter.png"
    property string videoPlayerMenuIcone: "movie.png"
    property string weatherMenuIcone: "weather.png"
    property string gamesMenuIcone: "games.png"

    property string currentHeaderMenu: mainMenu
    property string currentHeaderMenuIcone: mainMenuIcone
    // Get current date and time
    property var currentDate: new Date()
    property string currentDateTime: {
        // Format the date manually using Date methods
        var day = currentDate.getDate()
        var month = currentDate.getMonth() + 1 // Months are 0-based
        var year = currentDate.getFullYear()
        var hours = currentDate.getHours()
        var minutes = currentDate.getMinutes()
        var seconds = currentDate.getSeconds()

        // Add leading zero if needed
        day = day < 10 ? '0' + day : day
        month = month < 10 ? '0' + month : month
        hours = hours < 10 ? '0' + hours : hours
        minutes = minutes < 10 ? '0' + minutes : minutes
        seconds = seconds < 10 ? '0' + seconds : seconds

        return day + '/' + month + '/' + year + '   ' + hours + ':' + minutes + ':' + seconds
    }

    // Timer to update the date every second
    Timer {
        id: updateTimer
        interval: 500 // 1000 milliseconds = 1 second
        running: true
        repeat: true
        onTriggered: {
            currentDate = new Date() // Update current date and time
        }
    }

    function setMenuHeader(menuName) {
        switch (menuName) {
        case Enum.WindowName.Menu:
        {
            currentHeaderMenu = mainMenu
            currentHeaderMenuIcone = mainMenuIcone
            break
        }
        case Enum.WindowName.Weather:
        {
            currentHeaderMenu = weatherMenu
            currentHeaderMenuIcone = weatherMenuIcone
            break
        }
        case Enum.WindowName.VideoPlayer:
        {
            currentHeaderMenu = videoPlayerMenu
            currentHeaderMenuIcone = videoPlayerMenuIcone
            break
        }
        default:
            console.warn("currentHeaderMenu not found")
            break
        }
    }

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#343447"
        }
        GradientStop {
            position: 1.0
            color: "#0d162e"
        }
    }

    Image {
        id: iconePowerOff
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0.02 * parent.width
        height: 0.6 * parent.height
        width: height
        fillMode: Image.PreserveAspectFit
        source: ResourcesComponents.rootAssetsPath + "power.png"
    }

    Item {
        anchors.centerIn: parent
        height: parent.height
        width: childrenRect.width
        Image {
            id: iconeMenu
            anchors.verticalCenter: parent.verticalCenter
            height: 0.8 * parent.height
            width: height
            fillMode: Image.PreserveAspectFit
            source: ResourcesComponents.rootAssetsPath + header.currentHeaderMenuIcone
        }
        Text {
            id: name
            text: qsTr(header.currentHeaderMenu)
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            anchors.left: iconeMenu.right
            anchors.leftMargin: 0.02 * header.width
            color: "white"
            font.pixelSize: 0.5 * header.height
        }
    }

    Text {
        id: textCurrentDateTime
        text: header.currentDateTime
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 0.74 * header.width
        color: "white"
        font.pixelSize: 0.5 * header.height
    }
}
