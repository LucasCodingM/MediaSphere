import QtQuick
import QtQuick.Controls.Basic
import "../../../"

Rectangle {
    id: controlMediaButtons
    width: 0.85 * parent.width
    height: 0.20 * parent.height
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    color: "transparent"
    opacity: enabled ? 1 : 0

    property Item mediaPlayer
    property alias mediaProgression: mediaProgression
    property alias volumeSlider: volumeSlider
    property alias buttonAudio: buttonAudio
    property alias buttonPausePlay: buttonPausePlay

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        onHoveredChanged: {
            if (mouseArea.containsMouse) {
                controlMediaButtons.enabled = 1
            } else {
                controlMediaButtons.enabled = 0
            }
        }
    }

    Item {
        id: containerUp
        anchors.top: parent.top
        width: parent.width
        height: parent.height / 2
        Slider {
            id: mediaProgression
            hoverEnabled: false
            value: 0.5
            anchors.centerIn: parent
            onPressedChanged: {
                if (pressed && buttonPausePlay.isPlaying) {
                    controlMediaButtons.mediaPlayer.pause()
                }
            }
            onPositionChanged: {
                if (pressed)
                    controlMediaButtons.mediaPlayer.position = mediaProgression.position
                            * controlMediaButtons.mediaPlayer.duration
            }

            background: Rectangle {
                x: mediaProgression.leftPadding
                y: mediaProgression.topPadding + mediaProgression.availableHeight / 2 - height / 2
                implicitWidth: controlMediaButtons.width
                implicitHeight: 0.09 * containerUp.height

                width: mediaProgression.availableWidth
                height: implicitHeight
                radius: 0.28 * parent.height
                color: "#bdbebf"
                opacity: 0.5

                Rectangle {
                    width: mediaProgression.visualPosition * parent.width
                    height: parent.height
                    color: "#2f63a8"
                    radius: 0.28 * parent.height
                }
            }
            handle: Rectangle {
                x: mediaProgression.leftPadding + mediaProgression.visualPosition
                   * (mediaProgression.availableWidth - width)
                y: mediaProgression.topPadding + mediaProgression.availableHeight / 2 - height / 2
                implicitWidth: 0.029 * containerUp.width
                implicitHeight: implicitWidth
                radius: parent.height / 2
                color: mediaProgression.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#bdbebf"
            }
        }
    }
    Item {
        id: containerDown
        width: parent.width
        height: parent.height / 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        Row {
            anchors.centerIn: parent
            spacing: 0.046 * parent.width

            ButtonReplay {
                id: buttonReplay
                width: 0.08 * parent.width
                height: width
                hoverEnabled: false
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    controlMediaButtons.mediaPlayer.replay()
                }
            }
            ButtonAccelerate {
                id: buttonAccelerateBack
                width: 0.08 * parent.width
                height: width
                hoverEnabled: false
                anchors.verticalCenter: parent.verticalCenter
                mirror: true
                onClicked: {
                    const currentPosition = controlMediaButtons.mediaPlayer.position
                    controlMediaButtons.controlMediaButtons.mediaPlayer.position = Math.max(
                                (currentPosition - 0.02
                                 * controlMediaButtons.mediaPlayer.duration), 0)
                }
            }

            ButtonPausePlay {
                id: buttonPausePlay
                width: 0.08 * parent.width
                height: width
                hoverEnabled: false
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if (isPlaying)
                        controlMediaButtons.mediaPlayer.pause()
                    else
                        controlMediaButtons.mediaPlayer.play()
                }
            }

            ButtonAccelerate {
                id: buttonAccelerateNext
                width: 0.08 * parent.width
                height: width
                hoverEnabled: false
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    const currentPosition = controlMediaButtons.mediaPlayer.position
                    controlMediaButtons.mediaPlayer.position = Math.min(
                                (currentPosition + 0.02
                                 * controlMediaButtons.mediaPlayer.duration),
                                controlMediaButtons.mediaPlayer.duration)
                }
            }

            ButtonStop {
                id: buttonStop
                width: 0.08 * parent.width
                height: width
                hoverEnabled: false
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    controlMediaButtons.mediaPlayer.stop()
                    ResourcesComponents.setWindowVisibility(
                                Window.AutomaticVisibility)
                }
            }

            ButtonAudio {
                id: buttonAudio
                hoverEnabled: false
                width: 0.08 * parent.width
                height: width
                anchors.verticalCenter: parent.verticalCenter
            }

            Slider {
                id: volumeSlider
                hoverEnabled: false
                value: 0.5
                anchors.verticalCenter: parent.verticalCenter

                background: Rectangle {
                    x: volumeSlider.leftPadding
                    y: volumeSlider.topPadding + volumeSlider.availableHeight / 2 - height / 2
                    implicitWidth: 0.23 * containerDown.width
                    implicitHeight: 4
                    width: volumeSlider.availableWidth
                    height: implicitHeight
                    radius: 0.28 * parent.height
                    color: "#bdbebf"
                    opacity: 0.5

                    Rectangle {
                        width: volumeSlider.visualPosition * parent.width
                        height: parent.height
                        color: "#2f63a8"
                        radius: 0.28 * parent.height
                    }
                }

                handle: Rectangle {
                    x: volumeSlider.leftPadding + volumeSlider.visualPosition
                       * (volumeSlider.availableWidth - width)
                    y: volumeSlider.topPadding + volumeSlider.availableHeight / 2 - height / 2
                    implicitWidth: 0.02 * containerUp.width
                    implicitHeight: implicitWidth
                    radius: parent.height / 2
                    color: volumeSlider.pressed ? "#f0f0f0" : "#f6f6f6"
                    border.color: "#bdbebf"
                }
            }
        }
    }
}
