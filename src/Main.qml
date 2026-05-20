import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Layouts

import "View/OptionWindow"

Window {
    width: 1920
    height: 1080
    property string teme: "Светлая"
    property bool teme_flag: true
    property real swidth : width / 100
    property real sheight : height / 100
    color: "red"
    Connections
    {
        target: optionWindow
        onDataUpdated:
        {

        }
    }

    property string opt_w: "View/OptionWindow/OptionWindow_V.qml"
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
                onClicked:
                {
                    win_loader.source = opt_w
                    win_loader.item.show()
                    win_loader.item.raise()
                    win_loader.item.requestActivate()
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
            x: swidth * 82.5
            width: swidth * 15
            height: sheight * 22.8
            Rectangle
            {
                id: img_rect_m;
                height: sheight * 7.5
                width: swidth * 4.25
                x: swidth * 5.25
                color: "green"
                radius: width / 2
                Image
                    {
                        id: profile_img_m;
                        //source: "file"
                        clip: true
                        anchors.fill: parent
                    }
            }
            Rectangle
            {
                id: name_sername_rect
                width: swidth * 12
                height: sheight * 2.5
                x: swidth * 1.5
                y: img_rect_m.y + img_rect_m.height + sheight * 1.6
                Text
                {
                    id:name_sername
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    font.pixelSize: swidth * 1.125
                    text: "Aкакий Акакьевич"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                }
            }
            Rectangle
            {
                id: lvl_rect
                width: swidth * 8
                height: sheight * 2.5
                x: swidth * 3.5
                y: name_sername_rect.y + name_sername_rect.height
                Text
                {
                    id:lvl
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    font.pixelSize: swidth
                    text: "Менеджер"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                }
            }

            MenuItem
            {
                height: sheight * 2.5
                text: "Настройка профиля";
                font.pixelSize: swidth * 1.25
            }
            MenuItem
            {
                height: sheight * 2.5
                text: "Опции";
                font.pixelSize: swidth * 1.25
                onClicked:
                {
                    win_loader.source = opt_w
                    win_loader.item.show()
                    win_loader.item.raise()
                    win_loader.item.requestActivate()
                }
            }
            MenuItem
            {
                height: sheight * 2.5
                text: "Тема: " + teme;
                font.pixelSize: swidth * 1.25
            }
            MenuItem
            {
                height: sheight * 2.5
                text: "Выход";
                font.pixelSize: swidth * 1.25
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
