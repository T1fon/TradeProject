#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
    , __model(this)
{
    if(!__model.createDB())
    {
        qDebug() << "Ошибка создания и проверки БД";
        return;
    }
}

