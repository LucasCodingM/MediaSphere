import QtQuick

ButtonTransparent {
    id: buttonReplay
    property bool isPlaying: false
    sIconName: isPlaying ? "pause.png" : "play.png"
}
