import QtQuick
import QtQuick.Controls

Button {
    id: buttonBack
    width: 100
    height: 100
    property string sPathIcone: "back.png"
    property real iconeWidth: width - 40
    property real iconeHeight: height - 40
    background: Rectangle {
        id: bgnRec
        radius: 37
        visible: true
        opacity: enabled ? 1 : 0.3
        color: "transparent"

        Image {
            id: icone
            source: ResourcesComponents.rootAssetsPath + buttonBack.sPathIcone
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: buttonBack.iconeWidth
            height: buttonBack.iconeHeight
        }
    }
}
