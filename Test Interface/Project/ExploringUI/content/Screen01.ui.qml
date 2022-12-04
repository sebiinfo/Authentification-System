/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.4
import QtQuick.Controls 6.4
import ExploringUI

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#191e2e"


    Text {
        id: label
        y: 266
        width: 1039
        height: 69
        color: "#ffffff"
        text: qsTr("Hello, welcome to your Authentification System!")
        anchors.top: button.bottom
        font.pointSize: 40
        font.family: "Times New Roman"
        anchors.horizontalCenterOffset: 1
        anchors.topMargin: -346
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: Constants.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: Constants.backgroundColor
                from: "#2294c6"
            }
        }
    }

    TextInput {
        id: textInput
        x: 699
        y: 339
        width: 523
        height: 94
        color: "#ffffff"
        text: qsTr("Select which option you would like to use:")
        font.pixelSize: 30
        font.styleName: "Italic"
        font.family: "Times New Roman"
    }

    Button {
        id: button
        x: 764
        y: 515
        width: 392
        height: 50
        text: qsTr("Access Group Information")
    }

    Button {
        id: button1
        x: 764
        y: 631
        width: 392
        height: 50
        text: qsTr("Check Belongingness")
    }

    App {
        id: app
        x: -488
        y: 473
    }
    states: [
        State {
            name: "clicked"
            when: button.checked

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:7}
}
##^##*/
