import QtQuick
import QtQuick.Controls

//window resolution: 1024x600
Button {
    id: buttonBlue
    width: 200
    height: 185
    property string sPathIcone: ""
    property real iconeWidth: width - 40
    property real iconeHeight: height - 40
    background: Rectangle {
        id: bgnRec
        radius: 37
        visible: true
        opacity: enabled ? 1 : 0.3
        border.color: buttonBlue.down ? "white" : "transparent"
        border.width: 2
        property color colorStart: buttonBlue.down ? "#0e1d30" : "#2f63a8"
        property color colorEnd: buttonBlue.down ? "black" : "#0e1d30"
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop {
                position: 0.0
                color: bgnRec.colorStart
            }
            GradientStop {
                position: 1.0
                color: bgnRec.colorEnd
            }
        }
        Image {
            id: icone
            source: ResourcesComponents.rootAssetsPath + buttonBlue.sPathIcone
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: buttonBlue.iconeWidth
            height: buttonBlue.iconeHeight
        }
    }
}
