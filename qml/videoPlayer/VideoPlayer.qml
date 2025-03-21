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
        id: buttonAddMovies
        anchors.right: parent.right
        anchors.verticalCenter: buttonBack.verticalCenter
        text: qsTr("Add movies")
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
                ResourcesComponents.setWindowVisibility(Window.FullScreen)
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

    MessageDialog {
        id: messageDialog
        buttons: MessageDialog.Ok
        title: qsTr("Error File")
        text: qsTr("File does not exist ") + player.source
    }

    Component {
        id: menuItemComponent

        MenuItem {}
    }

    //Context Menu
    Menu {
        id: contextMenu

        MenuItem {
            text: qsTr("Delete")
            onTriggered: {
                console.log("Delete triggered")
                gridView.currentItem.selfDelete()
            }
        }
    }

    GridView {
        id: gridView
        anchors.left: parent.left
        anchors.leftMargin: 0.12 * parent.width
        anchors.bottom: parent.bottom
        visible: !videoPlayer.isVideoVisible
        width: 0.7 * parent.width
        height: 0.7 * parent.height
        cellWidth: 0.16 * parent.width
        cellHeight: cellWidth
        clip: true
        model: player.getVideoSelectionModel()

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        delegate: Item {
            width: gridView.cellWidth
            height: gridView.cellHeight

            function selfDelete() {
                player.deleteVideo(model.videoUrl)
            }

            ButtonTransparent {
                width: parent.width
                height: parent.height
                source: model.thumbnail
                radius: 5
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: mouse => {
                                   if (mouse.button == Qt.RightButton) {
                                       // Show the context menu on right-click
                                       contextMenu.popup(mapToGlobal(mouse.x,
                                                                     mouse.y))
                                   } else
                                   parent.clicked()
                               }
                    onPressAndHold: mouse => {
                                        if (mouse.source === Qt.MouseEventNotSynthesized)
                                        contextMenu.popup(mapToGlobal(mouse.x,
                                                                      mouse.y))
                                    }
                }

                onClicked: {
                    player.source = model.videoUrl
                    if (player.sourceIsValid()) {
                        player.play()
                    } else
                        messageDialog.visible = true
                }
            }
            Text {
                id: textVideoName
                width: parent.width
                height: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0.1 * parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                font.pixelSize: 0.1 * parent.height
                wrapMode: Text.WordWrap
                elide: Text.ElideRight
                text: model.videoName
            }
        }
    }
}
