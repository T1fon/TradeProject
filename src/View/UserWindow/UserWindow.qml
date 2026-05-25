import QtQuick 2.15
import QtQuick.Controls 2.15

Window
{
    id: userMainWindow
    width: 400
    height: 600
    property int swidth: width / 100
    property int sheight: height / 100
    property bool adminFlag : true // заменить на статус
    property bool newFlag: true
    property bool managerFlag : false
    title: "Пользователь"
    color: "#D9D9D9"
    flags: Qt.Window

    Rectangle
    {
        id: statusRect
        height: sheight * 5
        width: swidth * 25
        visible: newFlag
        enabled: newFlag
        x: swidth * 5
        y: sheight * 4
        color: "#D9D9D9"
        Rectangle
        {
            id: statusTitle
            width: swidth * 10
            height: parent.height
            color: "#D9D9D9"
            Text
            {
                text: "Уровень допуска"
                font.pixelSize: swidth * 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WordWrap
            }
        }
        ComboBox
        {
            id: statusBox
            width: swidth * 9
            height: parent.height
            anchors.right: parent.right
            font.pixelSize: swidth * 2
            model: ["", "1", "2"]

        }
    }

    Rectangle
    {
        id: img_rect_m;
        height: sheight * 10
        width: swidth * 16
        x: swidth * 42.5
        y: sheight * 2
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
        id: nameRect
        width: parent.width
        height: sheight * 7
        y: sheight * 12
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: nameTitle
                font.pixelSize: swidth * 4
                text: statusBox.currentIndex === 2 ? "Имя" : "Наименование компании:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WordWrap
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                id: nameTextRect
                width: swidth * 53.5
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                color: nameText.text ? "white" : "red"
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: nameText
                    width: parent.width
                    height: parent.height
                    font.pixelSize: swidth * 3.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    onTextChanged:
                    {
                        nameTextRect.color = text ? "white" : "red"
                    }
                }
            }
        }
    }
    Rectangle
    {
        id: cityRect
        width: parent.width
        height: sheight * 7
        y: nameRect.y + nameRect.height
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: cityTitle
                font.pixelSize: swidth * 4
                text: statusBox.currentIndex === 2  ? "Фамилия" : "Город:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WordWrap
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                width: swidth * 53.5
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                color: "white"
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: cityText
                    width: parent.width
                    height: parent.height
                    font.pixelSize: swidth * 3.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                }
            }
        }
    }
    Rectangle
    {
        id: innRect
        width: parent.width
        visible: statusBox.currentIndex === 2 ? false: true
        enabled: statusBox.currentIndex === 2 ? false: true
        height: sheight * 7
        y: cityRect.y + cityRect.height
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: innTitle
                font.pixelSize: swidth * 4
                text: "ИНН:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WordWrap
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                id: innTextRect
                width: swidth * 53.5
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                color: innText.text ? "white" : "red"
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: innText
                    width: parent.width
                    height: parent.height
                    font.pixelSize: swidth * 3.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    onTextChanged:
                    {
                        innTextRect.color = text ? "white" : "red"
                    }
                }
            }
        }
    }
    Rectangle
    {
        id: addRect
        visible: statusBox.currentIndex === 2 ? false: true
        enabled: statusBox.currentIndex === 2 ? false: true
        width: parent.width
        height: sheight * 7
        y: innRect.y + innRect.height
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: addTitle
                font.pixelSize: swidth * 4
                text: "Адрес:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WordWrap
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                width: swidth * 53.5
                height: sheight * 6.5
                x: swidth * 1.5
                y: sheight
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: addText
                    width: parent.width
                    height: implicitHeight
                    font.pixelSize: swidth * 2.2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }
        }
    }
    Rectangle
    {
        id: phonesRect
        visible: statusBox.currentIndex === 2 ? false: true
        enabled: statusBox.currentIndex === 2 ? false: true
        width: parent.width
        height: sheight * 9
        y: addRect.y + addRect.height + sheight * 4
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: phonesTitle
                font.pixelSize: swidth * 4
                text: "Телефоны:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                width: swidth * 53.5
                height: sheight * 6.5
                x: swidth * 1.5
                y: sheight
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: phonesText
                    width: parent.width
                    height: implicitHeight
                    font.pixelSize: swidth * 2.2
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    anchors.fill: parent
                }
            }
        }
    }
    Rectangle
    {
        id: emailsRect
        visible: statusBox.currentIndex === 2 ? false: true
        enabled: statusBox.currentIndex === 2 ? false: true
        width: parent.width
        height: sheight * 9
        y: phonesRect.y + phonesRect.height
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: emailsTitle
                font.pixelSize: swidth * 4
                text: "Электр. почты:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                width: swidth * 53.5
                height: sheight * 6.5
                x: swidth * 1.5
                y: sheight * 1.5
                border.color: "black"
                border.width: swidth * 0.25
                color: "white"
                TextEdit
                {
                    id: pemailsText
                    width: parent.width
                    height: implicitHeight
                    font.pixelSize: swidth * 2.2
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }
        }
    }
    Rectangle
    {
        id: deleterTextRect
        visible: adminFlag
        enabled: adminFlag
        y: statusBox.currentIndex === 2 ? cityRect.y + cityRect.height : emailsRect.y + emailsRect.height
        x: swidth
        width: swidth * 25
        height: sheight * 4
        color: "#D9D9D9"
        Text {
            id: deleterText
            font.pixelSize: swidth * 3
            text: "Данные для входа"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignBottom
            anchors.fill: parent
        }

    }

    Rectangle
    {
        id: deleter
        visible: adminFlag
        enabled: adminFlag
        width: parent.width
        height: sheight * 0.5
        y: deleterTextRect.y + deleterTextRect.height
        color: "black"
    }
    Rectangle
    {
        id: managerRect
        visible: adminFlag
        enabled: adminFlag
        width: parent.width
        height: sheight * 7
        y: deleter.y + deleter.height
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: managerTitle
                font.pixelSize: swidth * 4
                text: "Ведущий менеджер:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                id: managerBoxRect
                width: swidth * 35
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                border.color: "black"
                border.width: swidth * 0.25
                ComboBox
                {
                    id: managerComboBox
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    model: usWind.getManagerNames()
                    font.pixelSize: swidth * 3.5
                }
            }
        }

    }
    Rectangle
    {
        id: loginRect
        width: parent.width
        height: sheight * 7
        y: managerRect.y + managerRect.height
        visible: adminFlag
        enabled: adminFlag
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: loginTitle
                font.pixelSize: swidth * 4
                text: "Логин:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                id: loginTextRect
                width: swidth * 45
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                color: loginText.text ? "white" : "red"
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: loginText
                    width: parent.width
                    height: parent.height
                    font.pixelSize: swidth * 3.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    onTextChanged:
                    {
                        nameTextRect.color = text ? "white" : "red"
                    }
                }
            }
        }
    }
    Rectangle
    {
        id: passRect
        width: parent.width
        height: sheight * 7
        y: loginRect.y + loginRect.height
        visible: adminFlag
        enabled: adminFlag
        color: "#D9D9D9"
        Rectangle
        {
            height: parent.height
            width: swidth * 40
            color: "#D9D9D9"
            Text {
                id: passTitle
                font.pixelSize: swidth * 4
                text: "Пароль:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle
        {
            width: swidth * 60
            height: parent.height
            x: swidth * 40
            color: "#D9D9D9"
            Rectangle
            {
                id: passTextRect
                width: swidth * 45
                height: sheight * 5
                x: swidth * 1.5
                y: sheight * 1.5
                color: loginText.text ? "white" : "red"
                border.color: "black"
                border.width: swidth * 0.25
                TextEdit
                {
                    id: passText
                    width: parent.width
                    height: parent.height
                    font.pixelSize: swidth * 3.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    onTextChanged:
                    {
                        nameTextRect.color = text ? "white" : "red"
                    }
                }
            }
        }
    }
    Rectangle
    {
        id: saveButtonRect
        width: swidth * 30
        height: sheight * 6.5
        x: swidth * 10
        y: adminFlag ? passRect.y + passRect.height + sheight * 2 :
                                                (managerFlag ? cityRect.y + cityRect.height + sheight * 2 : emailsRect.y + emailsRect.height + sheight * 2)
        border.width: swidth * 0.5
        color: "#D9D9D9"
        Button
        {
            id: saveButton
            width: parent.width
            height: parent.height
            anchors.fill: parent
            text: newFlag ? "Создать" : "Изменить"
            font.pixelSize: swidth * 3.5
        }
    }
    Rectangle
    {
        id: cancelButtonRect
        width: swidth * 30
        height: sheight * 6.5
        x: swidth * 60
        y: adminFlag ? passRect.y + passRect.height + sheight * 2 :
                                                (managerFlag ? cityRect.y + cityRect.height + sheight * 2 : emailsRect.y + emailsRect.height + sheight * 2)
        border.width: swidth * 0.5
        color: "#D9D9D9"
        Button
        {
            id: cancelButton
            width: parent.width
            height: parent.height
            anchors.fill: parent
            text: "Отмена"
            font.pixelSize: swidth * 3.5
            onClicked:
            {
                userMainWindow.close()
            }
        }
    }
}
