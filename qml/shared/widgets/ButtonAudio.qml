import QtQuick

ButtonTransparent {
    id: buttonReplay
    sIconName: checked ? "mute.png" : "audio.png"
    onClicked: checked = !checked
}
