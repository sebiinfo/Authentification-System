/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.4
import QtQuick.Controls 6.4
import UntitledProject

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#2f2f2f"

    TextField {
        id: username
        x: 854
        y: 470
        width: 371
        height: 38
        font.family: "Times New Roman"
        font.pointSize: 14
        placeholderText: qsTr("Text Field")
    }

    Label {
        id: label1
        x: 695
        y: 474
        color: "#ffffff"
        text: qsTr("Username:")
        font.pointSize: 21
        font.family: "Times New Roman"
    }

    Label {
        id: label2
        x: 693
        y: 549
        color: "#ffffff"
        text: qsTr("Password:")
        font.pointSize: 21
        font.family: "Times New Roman"
    }

    Label {
        id: label3
        x: 499
        y: 250
        width: 922
        height: 58
        color: "#ffffff"
        text: qsTr("Welcome to your Authentification System! ")
        font.pointSize: 40
        font.family: "Times New Roman"
    }

    Label {
        id: label4
        x: 693
        y: 360
        color: "#ffffff"
        text: qsTr("To continue please log in below:")
        rotation: 0.164
        font.pointSize: 31
        font.family: "Times New Roman"
    }

    Button {
        id: forgot
        x: 698
        y: 679
        width: 268
        height: 48
        opacity: 0.9
        text: qsTr("Forgot Password")
        font.pointSize: 18
        font.family: "Times New Roman"
    }

    Button {
        id: create
        x: 1549
        y: 67
        width: 283
        height: 49
        opacity: 0.9
        text: qsTr("Create an account")
        font.pointSize: 20
        font.family: "Times New Roman"
    }

    TextField {
        id: password
        x: 854
        y: 544
        width: 371
        height: 40
        font.family: "Times New Roman"
        font.pointSize: 14
        placeholderText: qsTr("Text Field")
    }

    Button {
        id: login
        x: 1033
        y: 679
        width: 192
        height: 48
        opacity: 0.9
        text: qsTr("Login")
        font.pointSize: 20
        font.family: "Times New Roman"

        Connections {
            target: login
            onPressed: console.log("button2.pressed")
        }
    }

    states: [
        State {
            name: "forgot_password"
            when: forgot.checked
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
