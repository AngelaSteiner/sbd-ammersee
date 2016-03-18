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
        color: "#2c5a85"

        Text {
            text: "SB Delphin 03 - Ammerseeschwimmen"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
            font.bold: true
            color: "#ffffff"
        }
    }

    Rectangle {
        id: content
        anchors.top: header.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#2c5a85"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

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
                id: entry
                //color: index % 2 == 0 ? "#7395b6" : "#AAAAAA"
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40

                Text {
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle {
                    anchors.bottom: entry.bottom
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    color: "#000"
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
            color: "#2c5a85"

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

