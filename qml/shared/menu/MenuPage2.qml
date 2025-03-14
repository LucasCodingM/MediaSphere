import QtQuick
import "../widgets"

Item {
    width: 1024
    height: 600
    id: menuPage2
    ButtonBlueGradient {
        id: buttonParameter
        x: 0.15 * parent.width
        y: 0.12 * parent.height
        width: 0.2 * parent.width
        height: 0.3 * parent.height
        sIconName: "parameter"
        enabled: false
    }
}
