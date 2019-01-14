import QtQuick 2.7
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    width: 320
    height: 480
    title: qsTr("Story viewer")


    Rectangle {
        id: inventaryBox
        width: parent.width // / 2
        height: parent.height * 0.15
        border.color: "green";
        border.width: 1;
        anchors.right: parent.right
        anchors.top: answerBrouser.bottom
        Inventary {
            id: inventary
            anchors.fill: parent
        }
    }

    TextArea {
        id: answerBrouser
        width: parent.width
        height: parent.height * 0.5
        text: viewer.answer
    }


    Rectangle {
        id: jumplistBox
        width: parent.width
        height: parent.height * 0.3
        border.color: "green";
        border.width: 1;
        anchors.right: parent.right
        anchors.top: borderBox.bottom
        anchors.bottom: parent.bottom
        JumpList {            
            anchors.fill: parent
        }
    }
    Rectangle {
        id: borderBox
        anchors.top: inventaryBox.bottom
        anchors.right: parent.right
        width: parent.width
        height: parent.height * 0.07
        color: "green"

        Rectangle {
            id: backButton           
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
                   viewer.onJumpBack()                    
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

