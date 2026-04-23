import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Layouts

import "View/OptionWindow"

Window {
    width: 1920
    height: 1080
    property real swidth : width / 100
    property real sheight : height / 100
    color: "red"

    Loader
    {
        id: win_loader
        source: ""
    }

    visible: true
    title: qsTr("TradeProject ")

    Rectangle
    {
        width: parent.width
        height: sheight * 3.5
        color: "white"
        Row
        {
            width: parent.width
            height: sheight * 3.5
            Button
            {
                id: main_but
                height: parent.height
                width: swidth * 6
                Text
                {
                    width: parent.width
                    height: parent.height
                    text: qsTr("Главная")
                    font.pixelSize: swidth * 0.75
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle
                {
                    border
                    {
                        color: "black"
                        width: swidth * 0.05
                    }
                    radius: 0
                }
            }
            Rectangle
            {
                id: menu_rect
                width: 0
                height: 0
                visible: false
                Menu
                {
                    id: optionsMenu
                    y: filtre_but.y + filtre_but.height
                    x: filtre_but.x
                    width: swidth * 8
                    height: sheight * 9
                    MenuItem
                    {
                        height: sheight * 2.9
                        text: "Действие 1";
                        font.pixelSize: swidth * 0.75
                        onTriggered: console.log("Действие 1")
                    }
                    MenuItem
                    {
                        height: sheight * 2.9
                        text: "Действие 2";
                        font.pixelSize: swidth * 0.75
                        onTriggered: console.log("Действие 1")
                    }
                    MenuItem
                    {
                        height: sheight * 2.9
                        text: "Действие 3";
                        font.pixelSize: swidth * 0.75
                        onTriggered: console.log("Действие 1")
                    }
                }
            }

            Button
            {
                id: filtre_but
                height: parent.height
                width: swidth * 6
                Text {
                    text: qsTr("Фильтры")
                    font.pixelSize: swidth * 0.75
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                }
                onClicked:
                {
                    optionsMenu.open()
                }
                background: Rectangle
                {
                    border
                    {
                        color: "black"
                        width: swidth * 0.05
                    }
                    radius: 0
                }
            }
            Button
            {
                id: opt_but
                height: parent.height
                width: swidth * 6
                Text
                {
                    width: parent.width
                    height: parent.height
                    text: qsTr("Опции")
                    font.pixelSize: swidth * 0.75
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle
                {
                    border
                    {
                        color: "black"
                        width: swidth * 0.05
                    }
                    radius: 0
                }
            }
        }
    }
    Rectangle
    {
        id: user_rect
        width: 0
        height: 0
        visible: false
        Menu
        {
            id: userMenu
            y: profile_rect.y + profile_rect.height
            x: swidth * 90
            width: swidth * 10
            height: sheight * 15
            Rectangle
            {

            }

            MenuItem
            {
                height: sheight * 2.9
                text: "Действие 2";
                font.pixelSize: swidth * 0.75
                onTriggered: console.log("Действие 1")
            }
            MenuItem
            {
                height: sheight * 2.9
                text: "Действие 3";
                font.pixelSize: swidth * 0.75
                onTriggered: console.log("Действие 1")
            }
        }
    }
    Button
    {
        id: profile_rect
        width: swidth * 4.5
        height: sheight * 6.3
        x: swidth * 95.47
        background: Rectangle
        {
            border
            {
                color: "black"
                width: swidth * 0.05
            }
            radius: 0
        }
        contentItem: Row
        {
            spacing: swidth * 0.05
            anchors.fill: parent
            Rectangle
            {
                id: img_rect;
                height: sheight * 5.5
                width: swidth * 3
                y: sheight * 0.225
                color: "yellow"
                radius: width / 2
                Image
                    {
                        id: profile_img;
                        //source: "file"
                        clip: true
                        anchors.fill: parent
                    }
            }
            Rectangle
            {
                width: swidth * 1.2
                height: sheight * 5.8
                y: sheight * 0.35
                Text
                {
                    text: qsTr("1")
                    font.pixelSize: swidth * 0.75
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                }
            }
        }
        onClicked:
        {
          userMenu.open()
        }
    }
}
