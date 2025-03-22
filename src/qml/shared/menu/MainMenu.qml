import QtQuick
import QtQuick.Controls

Item {
    id: mainMenu
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
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        count: view.count
        currentIndex: view.currentIndex
        delegate: Rectangle {

            implicitWidth: index === indicator.currentIndex ? implicitHeight : 2.5 * implicitHeight
            implicitHeight: 0.03 * mainMenu.height

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
