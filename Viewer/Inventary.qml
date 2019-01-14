import QtQuick 2.0

Item {
    GridView {
        id: inventary
        anchors.fill: parent
        anchors.margins: 1
        focus: true
        cellHeight: parent.height / 3.04
        cellWidth: parent.width / 5.035
        model: inventaryModel
        delegate: delegate
    }

    Component {
        id: delegate
        Rectangle {
            width: inventary.cellWidth - 1
            height: inventary.cellHeight - 1
            color: "#d1ccff"
            Row {
                spacing: 2
                anchors.centerIn: parent
                Text {                    
                    text: model.name
                }
                Text { text: model.count }

            }
        }
    }
}

