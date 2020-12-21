import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

import ToDo 1.0
ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            implicitWidth: 250
            implicitHeight: 250
            clip: true
            anchors.fill: parent
/*
        // integer model
        model: 100
*/
            /*
        // list model
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
            // c++ model
            // registered by qmlRegisterType<ToDoModel>("ToDo", 1, 0, "ToDoModel") in main.cpp
            // run qmake, it ensures the meta object compiler (MOC) is run
            model: ToDoModel {
                list: toDoList
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

    RowLayout {
        Button {
            text: qsTr("Add new item")
            onClicked: toDoList.appendItem()
            // make sure the button fills width of the rollout
            Layout.fillWidth: true
        }
        Button {
            text: qsTr("Remove comoleted")
            onClicked: toDoList.removeCompletedItems()
            Layout.fillWidth: true
        }
    }
}
