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
        x: 674
        y: 473
        color: "#ffffff"
        text: qsTr("Username:")
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
        id: create
        x: 1549
        y: 67
        width: 283
        height: 49
        opacity: 0.9
        text: qsTr("Create an account")
        font.pointSize: 20
        font.family: "Times New Roman"

        Connections {
            target: create
            onClicked: rectangle.state = "Create account"
        }
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
    }

    Label {
        id: label6
        x: 693
        y: 549
        color: "#ffffff"
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password1
        x: 854
        y: 544
        width: 371
        height: 40
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label7
        x: 1615
        y: 540
        visible: false
        color: "#ffffff"
        text: qsTr("Password:")
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: username1
        x: 1497
        y: 521
        width: 371
        height: 38
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label8
        x: 1776
        y: 527
        visible: false
        color: "#ffffff"
        text: qsTr("Username:")
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password2
        x: 1511
        y: 551
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label9
        x: 689
        y: 545
        color: "#ffffff"
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password3
        x: 1549
        y: 555
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label10
        x: 1744
        y: 540
        visible: false
        color: "#ffffff"
        text: qsTr("Password:")
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password4
        x: 1525
        y: 540
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label11
        x: 694
        y: 550
        color: "#ffffff"
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password5
        x: 1517
        y: 512
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label12
        x: 1776
        y: 540
        visible: false
        color: "#ffffff"
        text: qsTr("Password:")
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password6
        x: 1571
        y: 536
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label13
        x: 703
        y: 559
        color: "#ffffff"
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    TextField {
        id: password7
        x: 1541
        y: 521
        width: 371
        height: 40
        visible: false
        placeholderText: qsTr("Text Field")
        font.family: "Times New Roman"
        font.pointSize: 14
    }

    Label {
        id: label14
        x: 1540
        y: 599
        visible: false
        color: "#ffffff"
        text: qsTr("Password:")
        font.family: "Times New Roman"
        font.pointSize: 21
    }

    Label {
        id: label
        x: 674
        y: 549
        color: "#ffffff"
        text: qsTr("Password:")
        font.family: "Times New Roman"
        font.pointSize: 20
    }

    Button {
        id: forgot
        x: 674
        y: 679
        width: 274
        height: 48
        text: qsTr("Forgot Password")
        font.family: "Times New Roman"
        font.pointSize: 20

        Connections {
            target: forgot
            onClicked: rectangle.state = "forgot_password"
        }
    }

    states: [
        State {
            name: "forgot_password"
            when: forgot.checked
            
            PropertyChanges {
                target: label4
                x: 553
                y: 358
                text: qsTr("To continue please fill out the information below:")
            }
            
            PropertyChanges {
                target: label1
                x: 674
                y: 473
                width: 131
                height: 32
                text: qsTr("Username:")
            }
            
            PropertyChanges {
                target: rectangle
                color: "#2f2f2f"
            }
            
            PropertyChanges {
                target: login
                x: 1070
                y: 645
                width: 195
                height: 48
                text: qsTr("Login")
            }

            PropertyChanges {
                target: label3
                x: 499
                y: 250
                text: qsTr("Welcome to your Authentification System! ")
            }

            PropertyChanges {
                target: password3
                x: 1541
                y: 649
                visible: false
            }

            PropertyChanges {
                target: password2
                x: 1534
                y: 710
                visible: false
            }

            PropertyChanges {
                target: label10
                x: 1592
                y: 730
                visible: false
            }

            PropertyChanges {
                target: label8
                x: 213
                y: 497
                visible: false
                text: qsTr("Username:")
            }

            PropertyChanges {
                target: username1
                x: 1660
                y: 502
                visible: false
            }

            PropertyChanges {
                target: create
                visible: true
            }

            PropertyChanges {
                target: password7
                x: 1618
                y: 654
                visible: false
            }

            PropertyChanges {
                target: password6
                x: 1708
                y: 756
                visible: false
            }

            PropertyChanges {
                target: label7
                x: 1654
                y: 718
                visible: false
            }

            PropertyChanges {
                target: label14
                x: 1725
                y: 730
                visible: false
            }

            PropertyChanges {
                target: label
                text: qsTr("Email:")
            }

            PropertyChanges {
                target: forgot
                visible: false
            }
        },
        State {
            name: "Create account"

            PropertyChanges {
                target: label4
                x: 1509
                y: 666
                visible: false
            }

            PropertyChanges {
                target: username1
                x: 854
                y: 369
                visible: true
            }

            PropertyChanges {
                target: label8
                x: 602
                y: 373
                visible: true
                text: qsTr("Name:")
            }

            PropertyChanges {
                target: password2
                x: 854
                y: 441
                visible: true
            }

            PropertyChanges {
                target: label9
                x: 693
                y: 446
                visible: true
            }

            PropertyChanges {
                target: password3
                x: 854
                y: 441
                visible: true
            }

            PropertyChanges {
                target: label10
                x: 601
                y: 445
                visible: true
                text: qsTr("Last name:")
            }

            PropertyChanges {
                target: username
                x: 854
                y: 520
                visible: true
            }

            PropertyChanges {
                target: label1
                x: 602
                y: 524
                visible: true
            }

            PropertyChanges {
                target: password
                x: 854
                y: 750
                visible: true
            }

            PropertyChanges {
                target: label6
                x: 693
                y: 755
                visible: true
            }

            PropertyChanges {
                target: password1
                x: 855
                y: 750
                visible: true
            }

            PropertyChanges {
                target: label7
                x: 601
                y: 754
                visible: true
                text: qsTr("Confirm Password:")
            }

            PropertyChanges {
                target: login
                x: 1183
                y: 880
            }

            PropertyChanges {
                target: password4
                x: 855
                y: 673
                visible: true
            }

            PropertyChanges {
                target: label11
                x: 694
                y: 678
                visible: true
            }

            PropertyChanges {
                target: password5
                x: 855
                y: 673
                visible: true
            }

            PropertyChanges {
                target: label12
                x: 603
                y: 677
                visible: true
                text: qsTr("Password:")
            }

            PropertyChanges {
                target: password6
                x: 854
                y: 596
                visible: true
            }

            PropertyChanges {
                target: label13
                x: 693
                y: 601
                visible: true
            }

            PropertyChanges {
                target: password7
                x: 854
                y: 596
                visible: true
            }

            PropertyChanges {
                target: label14
                x: 604
                y: 600
                visible: true
                text: qsTr("Email:")
            }

            PropertyChanges {
                target: create
                visible: false
            }

            PropertyChanges {
                target: label
                x: 1696
                y: 719
                visible: false
            }

            PropertyChanges {
                target: forgot
                x: 1696
                y: 645
                visible: false
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
