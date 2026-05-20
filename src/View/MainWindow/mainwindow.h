#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "databasemodel.h"
#include <QStandardPaths>
#include <QDir>

class MainWindow: public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);
public slots:

private:
    DataBaseModel __model;
};

#endif // MAINWINDOW_H
