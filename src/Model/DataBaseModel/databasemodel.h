#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

class DataBaseModel
{
public:
    DataBaseModel(const QString& way);
    ~DataBaseModel();
    void setQuery(const QString& query);
    QString getResult();
private:
    QSqlDatabase __db;
    QString __query;
    QString __result;
    QString __db_way;
    void __compliteQuery();
};

#endif // DATABASEMODEL_H
