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
    QString Transaction = "0";
    QString INN;
    QString Sum;
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
    bool saveData(const QString& way);
    int getLength();
    QVector<XLData> getData();
    void setWay(const QString& way);
    bool saveToXml(const QVector<QString> tab, const QString& way, const QList<QVariantMap>& data);
private:
    QVector<XLData> __data;
    bool __extractData();
    bool __saveToXMl(const QVector<QString>& tabs, const QString& way, const QList<QVariantMap>& data);
    QString __way;
    int __length;
signals:
    void progressUpdated(int currentCount, int totalCount);
};

#endif // XLMODEL_H
