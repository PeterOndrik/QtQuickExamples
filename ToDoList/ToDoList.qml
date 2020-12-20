import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

import ToDo 1.0

Frame {
    ListView {
        implicitWidth: 250
        implicitHeight: 250
        clip: true
/*
        model: ListModel {
            ListElement {
                done: true
                description: "Wash the car"
            }
            ListElement {
                done: false
                description: "Fix the sink"
            }
        }
*/
        model: ToDoModel {
            list: ToDoModel
        }
        delegate: RowLayout {
            width: parent.width

            CheckBox {
                checked: model.done
                onClicked: model.done = checked
            }
            TextField {
                text: model.description
                onEditingFinished:  model.description = text
                Layout.fillWidth: true
            }
        }
    }
}
