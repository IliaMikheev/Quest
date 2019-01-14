import QtQuick 2.0
Item {
    ListView {
        id: jumpList
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1
        focus: true
        model: jumpListModel        

        delegate: Component {
            id: jumpListDelegate
            Rectangle {
                id: rect
                width: parent.width
                height: 30
                radius: height / 4
                color: "lightGreen"
                border.color: "darkGreen"               
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
                        viewer.onJumpSelected(model.index)
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

