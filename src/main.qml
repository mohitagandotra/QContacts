import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QSip")

    Button {
        id: fetchButton
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            enumerator.fetchContacts();
        }
        text: "Fetch Contacts"
    }

    ContactsList {
        anchors.fill: parent
        anchors.topMargin: fetchButton.height
    }
}
