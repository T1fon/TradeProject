#ifndef OPTIONWINDOW_V_H
#define OPTIONWINDOW_V_H
#include "XLModel.h"
#include "databasemodel.h"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class OptionWindow_V : public QObject
{
    Q_OBJECT
public:
    explicit OptionWindow_V(DataBaseModel* dbModel, QObject* parent);
    Q_INVOKABLE DataBaseModel* getDbModel() { return __dbModel; }
Q_SIGNALS:
    void dataLoaded();
public slots:
    QString saveDBWay(const QString& way);
    bool saveDataFromXL(const QString& xlWay, const QString& dbWay);
    bool saveDataToXL(const QString& tabs, const QString& way);
    QString getError();
    QString getDbWay();
private:
    XLModel __xlmodel;
    QString __mess;
    QString __dbWay;
    QString __defDbWay = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TradeProject/TradeProject.db";
    DataBaseModel* __dbModel = nullptr;
};

#endif // OPTIONWINDOW_V_H
