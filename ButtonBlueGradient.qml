import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

//window resolution: 1024x600
Button {
    id: butonBlueGradient
    width: 200
    height: 185
    //radius: 37
    background: Rectangle {
        id: bgnRec
        radius: 37
        color: "black"
        visible: true
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0.0
                color: "#2f63a8"
            }
            GradientStop {
                position: 1.0
                color: "black"
            }
        }

        // LinearGradient {
        //     anchors.fill: parent
        //     source: bgnRec
        //     start: Qt.point(0, 0)
        //     end: Qt.point(parent.height, parent.width)
        //     gradient: Gradient {
        //         GradientStop {
        //             position: 0.0
        //             color: "#2f63a8"
        //         }
        //         GradientStop {
        //             position: 1.0
        //             color: "black"
        //         }
        //     }
        // }
    }
}
