import QtQuick 2.0
Item {
    ListView {
        id: jumpList
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1
        focus: true
        /*
        header: Rectangle {
            width: parent.width
            height: 10
            gradient: Gradient {
                GradientStop {position: 0; color: "gray"}
                GradientStop {position: 0.7; color: "black"}
            }
            Text {
                anchors.centerIn: parent;
                color: "gray";
                text: "...";
                font.bold: true;
                font.pointSize: 7
            }
        }
        footer: Rectangle {
            width: parent.width
            height: 10
            gradient: Gradient {
                GradientStop {position: 0; color: "gray"}
                GradientStop {position: 0.7; color: "black"}
            }
            Text {
                anchors.centerIn: parent;
                color: "gray";
                text: "...";
                font.bold: true;
                font.pointSize: 7
            }
        }
        */
        model: jumpListModel
        //delegate: //jumpListDelegate

        delegate: Component {
            id: jumpListDelegate
            Rectangle {
                id: rect
                width: parent.width
                height: 30
                radius: height / 4
                color: "lightGreen"
                border.color: "darkGreen"
                //border.pixelAligned: 1=
                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: model.textRole
               }
                MouseArea {
                    width: parent.width
                    height: parent.height
                    onPressed: {
                        parent.color = "green"
                    }
                    onClicked: {
                        console.log("clicked " + model.index)
                        dialogController.onJumpSelected(model.index)
                    }
                   onCanceled: {
                        parent.color = "lightGreen"
                   }
                   onReleased: {
                       parent.color = "lightGreen"
                   }
                }
            }
        }
    }
}
