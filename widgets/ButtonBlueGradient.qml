import QtQuick
import QtQuick.Controls
import ".."

//window resolution: 1024x600
Button {
    id: buttonBlue
    width: 200
    height: 185
    property real marginIcon: 0.2
    property string sIconName: ""
    property alias radius: bgnRec.radius
    property real iconeWidth: width - marginIcon * width

    background: Rectangle {
        id: bgnRec
        radius: 0.185 * buttonBlue.width
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
            source: ResourcesComponents.rootAssetsPath + buttonBlue.sIconName
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: buttonBlue.iconeWidth
        }
    }
}
