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
        id: textField1
        x: 1000
        y: 480
        width: 221
        height: 38
        font.family: "Times New Roman"
        font.pointSize: 14
        placeholderText: qsTr("Text Field")
    }

    Label {
        id: label1
        x: 839
        y: 484
        color: "#ffffff"
        text: qsTr("Username:")
        font.pointSize: 20
        font.family: "Times New Roman"
    }

    Label {
        id: label2
        x: 844
        y: 559
        color: "#ffffff"
        text: qsTr("Password:")
        font.pointSize: 20
        font.family: "Times New Roman"
    }

    Label {
        id: label3
        x: 572
        y: 247
        width: 922
        height: 58
        color: "#ffffff"
        text: qsTr("Welcome to your Authentification System! ")
        font.pointSize: 40
        font.family: "Times New Roman"
    }

    Label {
        id: label4
        x: 823
        y: 359
        color: "#ffffff"
        text: qsTr("To continue please log in below")
        rotation: 0.164
        font.pointSize: 25
        font.family: "Times New Roman"
    }

    Label {
        id: label5
        x: 1009
        y: 667
        color: "#ffffff"
        text: qsTr("Forgot your password?")
        font.pointSize: 17
        font.family: "Times New Roman"
    }

    Button {
        id: button
        x: 1290
        y: 660
        width: 167
        height: 39
        opacity: 0.8
        text: qsTr("Click here")
        font.pointSize: 16
        font.family: "Times New Roman"
    }

    Button {
        id: button1
        x: 1592
        y: 42
        width: 283
        height: 49
        opacity: 0.8
        text: qsTr("Create an account")
        font.pointSize: 18
        font.family: "Times New Roman"
    }

    TextField {
        id: textField3
        x: 1000
        y: 554
        width: 221
        height: 40
        font.family: "Times New Roman"
        font.pointSize: 14
        placeholderText: qsTr("Text Field")
    }

    states: [
        State {
            name: "clicked"
            when: button.checked
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:3}D{i:6}D{i:9}
}
##^##*/
