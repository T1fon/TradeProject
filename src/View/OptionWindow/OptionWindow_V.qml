import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Dialogs

Window
{
    width: 600
    height: 400

    property real swidth : width / 100
    property real sheight : height / 100
    title: "Опции"
    color: "#D9D9D9"
    flags: Qt.Window

    Rectangle
    {
       id: dbWayBlockRect
       width: swidth * 90
       height: sheight * 7
       x: swidth * 5
       y: sheight * 5
       color: "#D9D9D9"

       Rectangle
       {
           id: dbDescRect
           width: swidth * 12
           height:  sheight * 5
           y: sheight
           color: "#D9D9D9"
           Text
           {
               text: qsTr("Путь к БД")
               width: parent.width
               height: parent.height
               anchors.fill: parent
               font.pixelSize: swidth * 2.8
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
           }
       }

       Rectangle
       {
           id: dbWayRect
           width: swidth * 60
           height: parent.height
           x: dbDescRect.y + dbDescRect.width + swidth * 2
           color: "white"
           border.color: "black"
           border.width: swidth * 0.05
           TextEdit
           {
               id: dbWay
               width: parent.width
               height: parent.height
               anchors.fill: parent
               clip: true
               font.pixelSize: swidth * 2
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               enabled: false
           }
       }

       Rectangle
       {
           id: dbWayButt
           width: swidth * 15
           height: parent.height
           x: dbDescRect.y + dbDescRect.width + dbWayRect.y + dbWayRect.width + swidth * 4.5
           border.color: "black"
           border.width: swidth * 0.5
           color: "#D9D9D9"
           Button
           {
               width: parent.width
               height: parent.height
               anchors.fill: parent
               text: "Изменить"
               font.pixelSize: swidth * 2.8
               onClicked:
               {
                   filer.open()
               }
           }
       }
    }
    FileDialog
    {
        id: filer
        onAccepted:
        {
            dbWay.text = filer.currentFile
        }
    }

    Rectangle
    {
        id: dbButRect
        width: swidth * 90
        height: sheight * 34
        x: swidth * 5
        y: dbWayBlockRect.height + dbWayBlockRect.y + sheight * 2
        color: "#D9D9D9"
        Rectangle
        {
            id: loadDbRect
            width: swidth * 18
            height: sheight * 7
            y: sheight * 3
            border.color: "black"
            border.width: swidth * 0.05
            Button
            {
                id: loadDbBut
                width: parent.width
                height: parent.height
                anchors.fill: parent
                text: "Загрузить базу"
                font.pixelSize: swidth * 2.2
                onClicked:
                {
                    if(dbWay.text !=="")
                        filerLoad.open()
                    else
                    {
                        mess.text = "Не найден файл БД"
                        mess.open()
                    }
                }
            }
        }
        FileDialog
        {
            id: filerLoad
            onAccepted:
            {
            }
        }
        Rectangle
        {
            id: extractDbRect
            width: swidth * 18
            height: sheight * 7
            y: sheight * 3
            x: loadDbRect.x + loadDbRect.width + swidth * 5
            border.color: "black"
            border.width: swidth * 0.05
            Button
            {
                id: extractDbBut
                width: parent.width
                height: parent.height
                anchors.fill: parent
                text: "Выгрузить базу"
                font.pixelSize: swidth * 2.2
            }
        }
    }
    MessageDialog
    {
        id: mess
    }

    Rectangle
    {
        id: userText
        width: swidth * 20
        height: sheight * 6
        x: swidth * 5
        y: dbButRect.y + dbButRect.height
        color: "#D9D9D9"
        Text
        {
            text: qsTr("Работа с пользователями")
            width: parent.width
            height: parent.height
            anchors.fill: parent
            font.pixelSize: swidth * 2.5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

    }

    Rectangle
    {
        id: oneRowRect
        width: parent.width
        height: sheight * 0.5
        color: "black"
        y: userText.y + userText.height
    }

    Rectangle
    {
        id: userButRect
        width: swidth * 90
        height: sheight * 30
        x: swidth * 5
        y: oneRowRect.height + oneRowRect.y + sheight * 2
        color: "#D9D9D9"
        Rectangle
        {
            id: regUserRect
            width: swidth * 18
            height: sheight * 7
            y: sheight * 3
            border.color: "black"
            border.width: swidth * 0.05
            Button
            {
                id: regUserBut
                width: parent.width
                height: parent.height
                anchors.fill: parent
                text: "Регистрация"
                font.pixelSize: swidth * 2.2
            }
        }
        Rectangle
        {
            id: editUserRect
            width: swidth * 18
            height: sheight * 7
            y: sheight * 3
            x: loadDbRect.x + loadDbRect.width + swidth * 5
            border.color: "black"
            border.width: swidth * 0.05
            Button
            {
                id: editUserBut
                width: parent.width
                height: parent.height
                anchors.fill: parent
                text: "Редактирование"
                font.pixelSize: swidth * 2.2
            }
        }
    }


}
