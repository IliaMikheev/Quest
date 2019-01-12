import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextArea {
        text: dialogController.answer
    }

    Rectangle {
        id: inventaryBox
        width: parent.width / 2
        height: parent.height * 0.3
        border.color: "green";
        border.width: 1;
        anchors.right: parent.right
        anchors.top: parent.top
        Inventary {
            id: inventary
            anchors.fill: parent
        }
    }
    Rectangle {
        id: jumplistBox
        width: parent.width / 2
        height: parent.height * 0.63
        border.color: "green";
        border.width: 1;
        anchors.right: parent.right
        anchors.top: borderBox.bottom
        JumpList {
            //anchors.top: inventary.bottom
            anchors.fill: parent
        }
    }
    Rectangle {
        id: borderBox
        anchors.top: inventaryBox.bottom
        anchors.right: parent.right
        width: parent.width / 2
        height: parent.height * 0.07
        color: "green"

        Rectangle {
            id: backButton
            //text: "back"
            height: parent.height * 0.8
            width: text.width * 1.5
            anchors.right: parent.right
            anchors.rightMargin: parent.height * 0.1
            anchors.verticalCenter: parent.verticalCenter
            radius: height / 4
            color: "lightgreen"

            Text {
                id: text
                text: qsTr("back")
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    parent.color = "green"
                }
                onClicked: {
                    //console.log("clicked")
                    dialogController.onJumpBack()
                    //dialogController.jumpSelected(model.index)
                }
                onReleased: {
                    parent.color = "lightGreen"
                }

                onCanceled: {
                    parent.color = "lightGreen"
                }
            }
        }
    }

}
