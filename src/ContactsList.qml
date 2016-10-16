import QtQuick 2.0
//import com.qsip.qmlcomponents 1.0

Item {
    ListView {
        anchors.fill: parent
        model: contactsModel
        spacing: 2
        delegate: Rectangle {
            height: name.height + 10
            width: parent.width
            color: "ghostwhite"
            Text {
                id: name
                font.pointSize: 14
                anchors.verticalCenter: parent.verticalCenter
                text: contact_name + " " + contact_phone_numbers
            }
        }
    }
}
