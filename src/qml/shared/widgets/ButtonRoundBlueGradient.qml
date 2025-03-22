import QtQuick

Item {
    id: buttonRoundBlueGradient
    width: buttonBlueGradient.width + textButtonRoundBlueGradient.anchors.leftMargin
           + textButtonRoundBlueGradient.width
    height: 0.083 * parent.height
    anchors.right: parent.right
    anchors.rightMargin: 0.083 * parent.height
    property alias text: textButtonRoundBlueGradient.text
    property alias sIconName: buttonBlueGradient.sIconName

    signal clicked

    ButtonBlueGradient {
        id: buttonBlueGradient
        radius: parent.height
        height: parent.height
        width: height
        marginIcon: 0.4
        sIconName: "plus.png"
        onClicked: parent.clicked()
    }
    Text {
        id: textButtonRoundBlueGradient
        anchors.verticalCenter: buttonBlueGradient.verticalCenter
        anchors.left: buttonBlueGradient.right
        anchors.leftMargin: 0.5 * parent.height
        font.pixelSize: 0.6 * parent.height
        color: "white"
    }
}
