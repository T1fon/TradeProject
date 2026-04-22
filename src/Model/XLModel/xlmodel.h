#ifndef XLMODEL_H
#define XLMODEL_H

#include <QString>
#include <QColor>
#include "xlsxdocument.h"
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
    ~XLModel();
private:
    QVector<XLData> __data;
    bool __extractData();
    bool __saveData(const QString& way);
    QString __way;
    int __length;
signals:
    void progressUpdated(int currentCount, int totalCount);
};

#endif // XLMODEL_H
