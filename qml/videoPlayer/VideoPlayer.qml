import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Basic
import QtMultimedia
import VideoPlayerModule
import "../shared/widgets"
import "../../"

Item {
    id: videoPlayer
    anchors.fill: parent

    property bool isVideoVisible: false

    ButtonRoundBlueGradient {
        anchors.right: parent.right
        anchors.verticalCenter: buttonBack.verticalCenter
        text: "Add movies"
        sIconName: "plus.png"
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(
                           StandardPaths.MoviesLocation)[0]
        onAccepted: player.source = selectedFile
    }

    Button {
        anchors.centerIn: parent
        width: 50
        height: 50
        onClicked: player.play()
    }

    //Display a black background when the video is playing
    Rectangle {
        id: bgn
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
        }
        color: "black"
        visible: videoPlayer.isVideoVisible
    }

    // Create VideoPlayer object from C++ class
    VideoPlayer {
        id: player
        videoOutput: videoOutput
        onPlaybackStateChanged: {
            if (playbackState == MediaPlayer.PlayingState) {
                isVideoVisible = true
                controlMedia.buttonPausePlay.isPlaying = true
            } else if (playbackState == MediaPlayer.PausedState) {
                isVideoVisible = true
                controlMedia.buttonPausePlay.isPlaying = false
            } else {
                isVideoVisible = false
                controlMedia.buttonPausePlay.isPlaying = false
            }
        }
        onPositionChanged: {
            controlMedia.mediaProgression.value = player.position / player.duration
        }

        audioOutput: AudioOutput {
            volume: controlMedia.volumeSlider.value
            muted: controlMedia.buttonAudio.checked
        }
    }

    // Video display area
    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    ButtonBack {
        id: buttonBack
        x: 0.05 * parent.width
        y: 0.12 * parent.height

        onClicked: ResourcesComponents.loadComponent(Enum.WindowName.Menu)
        visible: !videoPlayer.isVideoVisible
    }

    // Control buttons
    ControlMedia {
        id: controlMedia
        mediaPlayer: player
        opacity: 0
        visible: videoPlayer.isVideoVisible
    }

    // ListView {
    //     width: parent.width
    //     height: parent.height
    //     model: ListModel {
    //         ListElement {
    //             row: 0
    //         }
    //         ListElement {
    //             row: 1
    //         }
    //         ListElement {
    //             row: 2
    //         }
    //     }

    //     delegate: Item {
    //         width: parent.width
    //         height: 200

    //         GridView {
    //             anchors.fill: parent
    //             cellWidth: 100
    //             cellHeight: 100
    //             model: jsonModel

    //             delegate: Rectangle {
    //                 width: 100
    //                 height: 100
    //                 color: "lightblue"
    //                 border.color: "black"
    //                 radius: 10

    //                 Text {
    //                     anchors.centerIn: parent
    //                     text: model.name
    //                 }
    //             }
    //         }
    //     }
    // }
}
