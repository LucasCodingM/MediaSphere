import QtQuick
import QtQuick.Controls
import "../../.."

Button {
    id: buttonBack
    width: 0.4 * parent.width
    height: 0.15 * parent.height
    property string textButtonBack: qsTr("MAIN MENU")
    property string sIconName: "back.png"

    background: Rectangle {
        id: bgnRec

        radius: 37
        visible: true
        opacity: enabled ? 1 : 0.3
        color: "transparent"
        border.color: buttonBack.pressed ? "white" : "transparent"

        Image {
            id: icone
            source: ResourcesComponents.rootAssetsPath + buttonBack.sIconName
            fillMode: Image.PreserveAspectFit
            mipmap: true
            anchors.left: parent.left
            anchors.leftMargin: 0.03 * parent.width
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: 0.5 * parent.height
        }

        Text {
            id: text
            anchors.left: icone.right
            anchors.leftMargin: 0.07 * parent.width
            anchors.verticalCenter: icone.verticalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: buttonBack.textButtonBack
            font.pixelSize: 0.09 * parent.width
            color: "white"
        }
    }
}
