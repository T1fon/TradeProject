#ifndef OPTIONWINDOW_V_H
#define OPTIONWINDOW_V_H
#include "XLModel.h"
#include <QObject>
#include <QStandardPaths>
#include <QDir>


class OptionWindow_V : public QObject
{
    Q_OBJECT
public:
    explicit OptionWindow_V(QObject *parent = nullptr);
Q_SIGNALS:
    void dataLoaded();
public slots:
    QString saveDBWay(const QString& way);
    bool saveDataFromXL(const QString& xlWay, const QString& dbWay);
    bool saveDataToXL(const QString& tabs, const QString& way);
    QString getError();
    QString getDbWay();
private:
    void __saveNewWay(const QString& newWay);
    XLModel __xlmodel;
    QString __mess;
    QString __dbWay;
    QString __defDbWay;
};

#endif // OPTIONWINDOW_V_H
