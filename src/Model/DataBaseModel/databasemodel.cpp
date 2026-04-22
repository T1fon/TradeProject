#include "databasemodel.h"

DataBaseModel::DataBaseModel(const QString& way)
{
    if(way.size() == 0) return;

    __db = QSqlDatabase::addDatabase("QSQLITE");
    __db.setDatabaseName(way);
    __db_way = way;
    if (!__db.open())
    {
        qDebug() << "Ошибка открытия базы данных:" << __db.lastError().text();
        return;
    }
    __db.close();
}

DataBaseModel::~DataBaseModel()
{
    if (__db.open())
    {
        __db.close();
    }
}

QString DataBaseModel::getResult()
{
    return __result;
}

void DataBaseModel::setQuery(const QString& query)
{
    __query = query;
}

void DataBaseModel::__compliteQuery()
{
    if(!__db.open())
    {
        qDebug() << "Ошибка открытия базы данных:" << __db.lastError().text();
        __result = "Ошибка открытия базы данных:" +__db.lastError().text();
        return;
    }
    if (__query.length() == 0)
    {
        __result = "Отстутствует запрос";
        return;
    }
    __result.clear();
    QSqlQuery query(__query);
    if (!query.exec())
    {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        __result = "Ошибка выполнения запроса:" + query.lastError().text();
        return;
    }
    if (query.size() == 0)
    {
        __result = "Запрос выполнен";
        __query.clear();
        __db.close();
        return;
    }
    QStringList rows;
    while (query.next())
    {
        QStringList fields;
        for (int i = 0; i < query.record().count(); ++i)
        {
            fields << query.value(i).toString();
        }
        rows << fields.join(", ");
    }
    __result = rows.join("\n");
    __query.clear();
    __db.close();
}
