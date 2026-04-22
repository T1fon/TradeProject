#ifndef XLMODEL_H
#define XLMODEL_H

#include <QString>
#include <QColor>
#include "xlsxdocument.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
struct XLData
{
    int transaction;
    double valSum;
    double sum;
    QString appointment;
    QString type;
    QString subtype;
    QString date;
};

class XLModel
{
public:
    XLModel();
    bool loadData(const QString& way);
    bool saveData(const QString& way);
    int getLength();
    void setWay(const QString& way);
    bool saveToXml(const QString& tabs, const QString& way, const QString& db_way);
    ~XLModel();
private:
    QVector<XLData> __data;
    bool __extractData();
    bool __saveData(const QString& way);
    bool __saveToXMl(const QVector<QString>& tabs, const QString& way, const QString& db_way);
    QString __way;
    int __length;
signals:
    void progressUpdated(int currentCount, int totalCount);
};

#endif // XLMODEL_H
