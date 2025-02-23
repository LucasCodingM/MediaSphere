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
        onAccepted: {
            player.appendVideoPath(selectedFile)
        }
    }

    //Display a black background when the video is playing
    Rectangle {
        id: bgn
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
            onClicked: controlMedia.enabled = !controlMedia.enabled
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
        enabled: false
        visible: videoPlayer.isVideoVisible
    }

    GridView {
        id: gridView
        anchors.left: parent.left
        anchors.leftMargin: 0.12 * parent.width
        anchors.bottom: parent.bottom
        visible: !videoPlayer.isVideoVisible
        width: 0.7 * parent.width
        height: 0.7 * parent.height
        cellWidth: 160
        cellHeight: 160
        clip: true
        model: player.getVideoSelectionModel()

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        delegate: Item {
            width: gridView.cellWidth
            height: gridView.cellHeight
            ButtonTransparent {
                width: parent.width
                height: parent.height
                //imageVisible: false
                //source: "image://thumbnailProvider/" + model.urlVideo
                Image {
                    anchors.centerIn: parent
                    width: 0.8 * parent.width
                    height: 0.8 * parent.height
                    source: model.thumbnail
                    fillMode: Image.PreserveAspectFit
                }
                onClicked: {
                    player.source = model.urlVideo
                    player.play()
                    ResourcesComponents.setWindowVisibility(Window.FullScreen)
                }
            }
        }
    }
}
