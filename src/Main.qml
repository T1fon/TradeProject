import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

import "View/OptionWindow"

Window {
    width: 1920
    height: 1080
    property real swidth : width / 100
    property real sheight : height / 100
    color: "red"

    visible: true
    title: qsTr("TradeProject ")
    Button
    {
        id: option_but
        width: swidth * 20
        height: sheight * 15
        x: swidth * 15
        Text
        {
            id: option_but_text
            text: qsTr("опции")
        }
        background: Rectangle
        {
           id: packet_zone_button_rec
           color: "#D9D9D9"
           //opacity: enabled ? 1 : 0.3
           border.color: "black"
           border.width: 1
           radius: 2
           Behavior on border.color
           {
                ColorAnimation { duration: 100 }
            }
        }
        onClicked:
        {
            loader.source = "View/OptionWindow/OptionWindow_V.qml"
        }
    }
    Rectangle
    {
        width: parent.width
        height: parent.height * 0.9
        y: sheight * 2.5
        color: "blue"
        Loader
        {
            id: loader
            anchors.fill: parent
            source: ""
        }
    }
}
