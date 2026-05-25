#include "xlmodel.h"

XLModel::XLModel(QObject *parent)
    : QObject(parent){}

bool XLModel::__extractData()
{
    QXlsx::Document __doc(__way);

    if(__doc.load())
    {
        __data.clear();
        __length = 0;
    }
    else return false;

    int row = 2;
    bool falseExit = true;
    __length = __doc.dimension().lastRow();
    QString target = "Банк налогоплательщика";

    for(int i = row; i <= __length; ++i)
    {
        auto cell = __doc.cellAt(QString("A%1").arg(i));
        if (cell && cell->value().toString() == target)
        {
            row = i;
            falseExit = false;
            break;
        }
    }
    if (falseExit) return false;
    if ((row + 5) < __length)
    {
        row = row + 5;
        int counter = 0;
        int currentCount = 200;
        XLData data;
        while( row < __length + 1)
        {
            auto nameCell = __doc.cellAt(QString("C%1").arg(row));
            if (!nameCell || nameCell->value().toString().isEmpty())
            {
                falseExit = true;
                break;
            }
            auto name =  __doc.cellAt(QString("U%1").arg(row));
            data.Name = name->value().toString();

            auto date = __doc.cellAt(QString("P%1").arg(row));
            QVariant cellValue = date->value();

            QDate dateObj = QDate::fromJulianDay(cellValue.toDouble() + 2415019); // преобразование
            data.Date = dateObj.toString("dd.MM.yyyy");

            auto inn =  __doc.cellAt(QString("V%1").arg(row));
            data.INN = inn->value().toString();
            auto trans = __doc.cellAt(QString("AB%1").arg(row));
            if (trans->value().toString() == "Дебет") data.Transaction = "0"; else data.Transaction = "1";

            if (data.Transaction == "0")
            {

                auto sum = __doc.cellAt(QString("Z%1").arg(row));
                data.Sum = sum->value().toString();
            }
            else
            {

                auto sum = __doc.cellAt(QString("AA%1").arg(row));
                data.Sum = sum->value().toString();
            }

            auto type = __doc.cellAt(QString("AC%1").arg(row));
            data.Type = type->value().toString();

            auto subtype = __doc.cellAt(QString("AD%1").arg(row));
            data.Subtype = subtype->value().toString();

            auto app = __doc.cellAt(QString("AE%1").arg(row));
            data.Appointment = app->value().toString();

            __data.push_back(data);
            ++row;
            ++counter;
            //if((counter % currentCount) == 0) progressUpdated(counter, __length);
        }
    }
    else return false;
    if (falseExit) return false;
    return true;
}
QVector<XLData> XLModel::getData()
{
    return __data;
}
bool XLModel::saveData(const QString& way)
{
    bool res;
    setWay(way);
    res = __extractData();
    return res;
}
int XLModel::getLength()
{
    return __length;
}
void XLModel::setWay(const QString& way)
{
    __way = way;
}
bool XLModel::saveToXml(const QVector<QString> tab, const QString& way, const QList<QVariantMap>& data)
{
    return __saveToXMl(tab, way, data);
}

bool XLModel::__saveToXMl(const QVector<QString>& tab, const QString& way, const QList<QVariantMap>& data)
{
    QXlsx::Document xlsx;

    for (int col = 0; col < tab.size(); ++col) {
        xlsx.write(1, col + 1, tab[col]);
    }

    for (int row = 0; row < data.size(); ++row)
    {
        const auto& rowData = data[row];
        for (int col = 0; col < tab.size(); ++col) {
            QString tabName = tab[col];
            QString value = rowData.value(tabName).toString();
            xlsx.write(row + 2, col + 1, value);
        }
    }

    bool result = xlsx.saveAs(way);
    if (!result) {
        qDebug() << "Ошибка сохранения файла в" << way;
        return false;
    }
    return result;
}

