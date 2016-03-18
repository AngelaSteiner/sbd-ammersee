import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Window {
    id: window1
    width: 800
    height: 600
    visible: true

    Rectangle {
        id: header
        height: 100
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        color: "#7D7D7D"

        Text {
            text: "SB Delphin - Ammerseeschwimmen"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
            font.bold: true
            color: "#DDDDDD"
        }
    }

    Rectangle {
        id: content
        anchors.top: header.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#4D4D4D"

        ListView {
            id: eventlist
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            width: parent.width - 150

            model: ListModel {
                ListElement {
                    name: "Grey"
                }

                ListElement {
                    name: "Red"
                }

                ListElement {
                    name: "Blue"
                }

                ListElement {
                    name: "Green"
                }
            }
            delegate: Rectangle {
                color: index % 2 == 0 ? "#EEEEEE" : "#AAAAAA"
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }

        Rectangle {
            id: btnArea
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.left: eventlist.right
            color: "#4D4D4D"

            Button {
                id: addEvent
                text: qsTr("Hinzufügen")
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 5
                onClicked: {
                    console.log("button clicked!")
                }
            }
        }
    }
}

