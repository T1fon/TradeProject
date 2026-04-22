#include "xlmodel.h"

XLModel::XLModel() {}


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
        auto cell = __doc.cellAt(QString("C%1").arg(i));
        if (cell && cell->value().toString() == target)
        {
            row = i;
            falseExit = false;
            break;
        }
    }
    if (falseExit) return false;
    if ((row + 4) < __length)
    {
        row = row + 4;
        int counter = 0;
        int currentCount = 200;
        XLData data;
        while( row < __length)
        {
            auto nameCell = __doc.cellAt(QString("C%1").arg(row));
            if (!nameCell || nameCell->value().toString().isEmpty())
            {
                falseExit = true;
                break;
            }
            auto date = __doc.cellAt(QString("C%16").arg(row));
            data.date = date->value().toString();

            auto trans = __doc.cellAt(QString("C%28").arg(row));
            if (trans->value().toString() == "Дебет") data.transaction = 0; else data.transaction = 1;

            if (data.transaction == 0)
            {
                auto valSum = __doc.cellAt(QString("C%24").arg(row));
                data.valSum = valSum->value().toDouble();

                auto sum = __doc.cellAt(QString("C%26").arg(row));
                data.sum = sum->value().toDouble();
            }
            else
            {
                auto valSum = __doc.cellAt(QString("C%25").arg(row));
                data.valSum = valSum->value().toDouble();

                auto sum = __doc.cellAt(QString("C%27").arg(row));
                data.sum = sum->value().toDouble();
            }

            auto type = __doc.cellAt(QString("C%29").arg(row));
            data.type = type->value().toString();

            auto subtype = __doc.cellAt(QString("C%30").arg(row));
            data.subtype = subtype->value().toString();

            auto app = __doc.cellAt(QString("C%31").arg(row));
            data.appointment = app->value().toString();

            __data.push_back(data);
            ++row;
            ++counter;
            if((counter % currentCount) == 0) progressUpdated(counter, __length);
        }
    }
    else return false;
    if (falseExit) return false;
    return true;
}
bool XLModel::__saveData(const QString& way)
{
    if(way.size() == 0) return false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(way);

    if (!db.open())
    {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    int needcount = 200;
    for(int i = 0; i < __data.size(); ++i)
    {
        query.prepare("INSERT INTO Data (id, Transaction, Sum, Appointment, Type, Subtype, Date) VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(i);
        query.addBindValue(__data[i].transaction);
        query.addBindValue(__data[i].sum);
        query.addBindValue(__data[i].appointment);
        query.addBindValue(__data[i].type);
        query.addBindValue(__data[i].subtype);
        query.addBindValue(__data[i].date);

        if (!query.exec())
        {
            qDebug() << "Ошибка вставки данных:" << query.lastError().text();
            return false;
        }
        ++i;
        if((i % needcount) == 0) progressUpdated(i, __length);
    }
    db.close();
    return true;
}
bool XLModel::loadData(const QString& way)
{
    bool res;
    res = __saveData(way);
    return res;
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
bool XLModel::saveToXml(const QString& tabs, const QString& way, const QString& db_way)
{
    QVector<QString> tab;
    if (tabs.length() == 0) return false;
    tab = tabs.split(';', Qt::SkipEmptyParts);
    return __saveToXMl(tab, way, db_way);
}

bool XLModel::__saveToXMl(const QVector<QString>& tabs, const QString& way, const QString& db_way)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_way);
    if (!db.open()) {
        qDebug() << "Ошибка открытия базы:" << db.lastError().text();
        return false;
    }
    QXlsx::Document xlsx;

    for (int col = 0; col < tabs.size(); ++col) {
        xlsx.write(1, col + 1, tabs[col]);
    }

    // Формируем запрос SELECT
    QString queryStr = "SELECT ";
    for (int i = 0; i < tabs.size(); ++i) {
        if (i != 0) queryStr += ", ";
        queryStr += tabs[i];
    }
    queryStr += " FROM Data";

    QSqlQuery query(queryStr);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        db.close();
        return false;
    }

    int rowIndex = 2; // дата с 2-й строки
    while (query.next()) {
        for (int col = 0; col < tabs.size(); ++col) {
            QString value = query.value(col).toString();
            xlsx.write(rowIndex, col + 1, value);
        }
        ++rowIndex;
    }

    // Сохраняем файл
    bool result = xlsx.saveAs(way);
    db.close();
    return result;
}

