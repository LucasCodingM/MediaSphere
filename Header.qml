import QtQuick

Rectangle {
    width: parent.width
    height: 0.08 * parent.height
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#343447"
        }
        GradientStop {
            position: 1.0
            color: "#0d162e"
        }
    }
}
