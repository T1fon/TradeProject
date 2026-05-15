#ifndef XLMODEL_H
#define XLMODEL_H

#include <QString>
#include <QColor>
#include "xlsxdocument.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
struct XLData
{
    int Transaction = 0;
    double valSum;
    double Sum;
    QString Appointment;
    QString Type;
    QString Subtype;
    QString Date;
};

class XLModel : public QObject
{
    Q_OBJECT
public:
    explicit XLModel(QObject *parent = nullptr);
    bool loadData(const QString& way);
    bool saveData(const QString& way);
    int getLength();
    void setWay(const QString& way);
    bool saveToXml(const QString& tabs, const QString& way, const QString& db_way);
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
