#ifndef OPTIONWINDOW_V_H
#define OPTIONWINDOW_V_H
#include "XLModel.h"
#include <QObject>;

#define DEF_WAY ""

class OptionWindow_V : public QObject
{
    Q_OBJECT
public:
    explicit OptionWindow_V(QObject *parent = nullptr);
    QString saveDBWay(const QString& way);
    bool saveDataFromXL(const QString& xlWay, const QString& dbWay);
    bool saveDataToXL(const QString& tabs, const QString& way);
    QString getError();
private:
    XLModel __xlmodel;
    QString __mess;
    QString __dbWay;
};

#endif // OPTIONWINDOW_V_H
