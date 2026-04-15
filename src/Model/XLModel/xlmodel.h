#ifndef XLMODEL_H
#define XLMODEL_H

#include <vector>
#include <QString>
struct CounterpartyData
{
    QString name;
    QString INN;
    QString KPP;
};


struct XLData
{
    CounterpartyData cpd;
    int transaction;
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
    bool getData(const QString& way);
    bool saveData(const QString& way);
    ~XLModel();
private:
    std::vector<XLData> __data;
    void __extractData(const QString& way);
    void __saveData(const QString& way);

};

#endif // XLMODEL_H
