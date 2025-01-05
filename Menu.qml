import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent
    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent

        MenuPage1 {
            id: firstPage
        }
        MenuPage2 {
            id: secondPage
        }
    }

    PageIndicator {
        id: indicator
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter

        count: view.count
        currentIndex: view.currentIndex
        delegate: Rectangle {

            implicitWidth: index === indicator.currentIndex ? 40 : 80
            implicitHeight: 40

            radius: width / 2
            color: "white"

            opacity: index === indicator.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

            required property int index

            Behavior on opacity {
                OpacityAnimator {
                    duration: 100
                }
            }
        }
    }
}
