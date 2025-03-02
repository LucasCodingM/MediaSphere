import QtQuick
import QtQuick.Controls
import "../../.."

Button {
    id: buttonTransparent
    width: 70
    height: 70
    property string sIconName: ""
    property real rotation: 0
    property alias mirror: icone.mirror
    property alias source: icone.source

    //property alias imageVisible: icone.visible
    background: Rectangle {
        opacity: enabled ? 1 : 0.3
        color: "transparent"
        border.color: buttonTransparent.down ? "white" : "transparent"
        border.width: 1
        radius: buttonTransparent.width / 4

        Image {
            id: icone
            source: buttonTransparent.sIconName
                    != "" ? ResourcesComponents.rootAssetsPath + buttonTransparent.sIconName : ""
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: height
            height: 0.8 * parent.height
            // Apply rotation using transform
            transform: Rotation {
                angle: rotation // Rotation angle in degrees
                origin.x: width / 2 // Center of the image to rotate around
                origin.y: height / 2
            }
        }
    }
}
