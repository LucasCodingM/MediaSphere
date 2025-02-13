import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtMultimedia
import VideoPlayerModule 1.0
import "../shared/widgets"
import "../../"

Item {
    id: videoPlayer
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
        text: "Add movies"
        sIconName: "plus.png"
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.standardLocations(
                           StandardPaths.MoviesLocation)[0]
        onAccepted: player.videoUrl = selectedFile
    }

    //Display a black background when the video is playing
    Rectangle {
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
        }
        color: "black"
        visible: player.isPlaying || player.isPaused
    }

    // Create VideoPlayer object from C++ class
    VideoPlayer {
        id: player
        videoUrl: "file:///home/lucas/Vidéos/chats.mp4" // Path to your video file
        videoOutput: videoOutput
    }

    // Video display area
    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    // Control buttons
    Rectangle {
        width: parent.width
        height: 100
        anchors.bottom: parent.bottom
        color: "#00000080"

        Row {
            anchors.centerIn: parent

            Button {
                text: "Play"
                onClicked: player.play()
            }

            Button {
                text: "Pause"
                onClicked: player.pause()
            }

            Button {
                text: "Stop"
                onClicked: player.stop()
            }

            Slider {
                id: volumeSlider
                from: 0
                to: 100
                value: 50
                onValueChanged: player.setVolume(value)
            }

            Switch {
                text: "Mute"
                onCheckedChanged: player.setMute(checked)
            }
        }
    }
}
