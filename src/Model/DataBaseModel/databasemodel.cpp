#include "databasemodel.h"

DataBaseModel::DataBaseModel(QObject *parent)
    : QSqlTableModel(parent)
{
    __pathDB = __standartPatt;
    __db = QSqlDatabase::addDatabase("QSQLITE", "dataBaseConnection");
    __db.setDatabaseName(__standartPatt);
    if(! __db.open())
    {
        qDebug() << "[DB_ERROR]: Не удалось создать БД. Возможно ее нету. ПРобуем создать заново";
        createDB();
        QVector<QString> params;
        params.append(__standartPatt);
        if(!insert("INSERT INTO Options (Dbway) VALUES (?)",params))
        {
            return;
        }
    }
    else
    {
        if (select("SELECT Dbway FROM Options"))
        {
            if (!__lastQueryResult.isEmpty())
            {
                QVariantMap firstRow = __lastQueryResult.at(0);
                QString newPath = firstRow.value("Dbway").toString();

                if (__pathDB != newPath && newPath != "")
                {
                    if (!setDatabasePath(newPath))
                    {
                        qDebug() << "Не удалось изменить путь к базе. Используется стандартный";
                    }
                }
            }
            else
            {
                qDebug() << "Результат запроса пуст!";
            }
        }
    }
}

bool DataBaseModel::setDatabasePath(const QString& path)
{
    if(__db.open())
    {
        QVector<QString> params;
        params.append(path);
        if(!insert("UPDATE Options SET Dbway = ?",params))
        {
            qDebug() << "[DB_ERROR]: Не удалось изменить местополжение";
            return false;
        }
        __db.close();
    }
    __db = QSqlDatabase::addDatabase("QSQLITE", "dataBaseConnection");
    __db.setDatabaseName(path);
    if (!__db.open()) {
        qDebug() << "[DB_ERROR]: Ошибка открытия базы";
        return false;
    }
    QVector<QString> a;
    a.append(path);
    if(!insert("UPDATE Options SET Dbway = ?",a))
    {
        return false;
    }
    __pathDB = path;
    return true;
}

bool DataBaseModel::request(const QString& query)
{
    QSqlQuery qu(__db);
    if(qu.exec(query))
        return true;
    else
    {
        __lastError = "[DB_ERROR] request fail:" + qu.lastError().text();
        return false;
    }
}

bool DataBaseModel::insert(const QString& query, const QVector<QString>& params)
{
    QSqlQuery qu(__db);
    qu.prepare(query);
    for(int i = 0; i < params.size(); ++i)
    {
        qu.bindValue(i, params[i]);
    }
    if (!qu.exec())
    {
        __lastError = "Не удалось выполнить запрос " + qu.lastError().text();
        qDebug() << "[DB_ERROR] insert fail " << qu.lastError().text();
        return false;
    }
    __lastId = qu.lastInsertId().toInt();
    return true;
}
bool DataBaseModel::insert(const QString& query, const QVector<int>& params)
{
    QSqlQuery qu(__db);
    qu.prepare(query);
    for(int i = 0; i < params.size(); ++i)
    {
        qu.bindValue(i, params[i]);
    }
    if (!qu.exec())
    {
        __lastError = "Не удалось выполнить запрос " + qu.lastError().text();
        qDebug() << "[DB_ERROR] insert fail " << qu.lastError().text();
        return false;
    }
    __lastId = qu.lastInsertId().toInt();
    return true;
}
bool DataBaseModel::select(const QString& query)
{
    QSqlQuery qu(__db);
    qu.prepare(query);
    __lastQueryResult.clear();
    if (!qu.exec(query))
    {
        __lastError = qu.lastError().text();
        qDebug() << "[DB_ERROR] Select failed:" << __lastError;
        return false;
    }
    QSqlRecord record = qu.record();
    while (qu.next())
    {
        QVariantMap row;
        for (int i = 0; i < record.count(); i++)
        {
            row[record.fieldName(i)] = qu.value(i);
        }
        __lastQueryResult.append(row);
    }
    return true;
}

bool DataBaseModel::createDB()
{

    QDir dir(QFileInfo(__standartPatt).absolutePath());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "[DB_ERROR]: Не удалось создать папку для БД:" << dir.absolutePath();
            return false;
        }
    }

    QStringList queries = {
        "CREATE TABLE IF NOT EXISTS Contr_question "
        "("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Question INTEGER,"
            "Answer STRING"
        ");",

        "CREATE TABLE IF NOT EXISTS Login "
        "("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Password STRING NOT NULL UNIQUE,"
            "Name STRING NOT NULL UNIQUE,"
            "lvl INTEGER NOT NULL DEFAULT 0,"
            "Question INTEGER REFERENCES Contr_question(id)"
        ");",

        "CREATE TABLE IF NOT EXISTS Manager "
        "("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Name STRING NOT NULL,"
            "Surname STRING,"
            "Login_id INTEGER REFERENCES Login(id),"
            "Img STRING"
        ");",

        "CREATE TABLE IF NOT EXISTS Client "
        "("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Name STRING NOT NULL,"
            "Phones STRING,"
            "INN STRING,"
            "Login_id INTEGER REFERENCES Login(id),"
            "Manager_id INTEGER REFERENCES Manager(Id),"
            "Img STRING"
        ");",

        "CREATE TABLE IF NOT EXISTS Counterparty "
        "("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Name STRING NOT NULL,"
            "INN STRING NOT NULL,"
            "KPP STRING,"
            "Img STRING,"
            "Client_id INTEGER REFERENCES Client(Id),"
            "OKVED STRING,"
            "City STRING,"
            "Address STRING,"
            "Phones STRING,"
            "Emails STRING"
        ");",

        "CREATE TABLE IF NOT EXISTS Data "
        "("
            "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Tranzaction STRING NOT NULL,"
            "Sum STRING NOT NULL,"
            "Appointment STRING,"
            "Type STRING,"
            "Subtype STRING,"
            "Date STRING NOT NULL"
        ");",


        "CREATE TABLE IF NOT EXISTS Counter_manager "
        "("
            "counter_id INTEGER REFERENCES Client(Id),"
            "manager_id INTEGER REFERENCES Data(Id)"
        ");",

        "CREATE TABLE IF NOT EXISTS Counter_data "
        "("
            "counter_id INTEGER REFERENCES Counterparty(Id),"
            "data_id INTEGER REFERENCES Data(Id)"
        ");",

        "CREATE TABLE IF NOT EXISTS Counter_client "
        "("
            "Counter_id INTEGER REFERENCES Counterparty(Id),"
            "Client_id INTEGER REFERENCES Client(Id)"
        ");",
        "CREATE TABLE IF NOT EXISTS Options "
        "("
        "Theme STRING,"
        "Dbway STRING"
        ");"
    };

    for (const QString &query : queries) {
        if (!request(query))
        {
            qDebug() << "[DB_ERROR]: Ошибка при создании таблицы:"
                     << __db.lastError().text()
                     << "\nЗапрос:" << query;
            return false;
        }
    }
    return true;
}
QString DataBaseModel::getDbWay()
{
    return __pathDB;
}

QString DataBaseModel::getLastError()
{
    return __lastError;
}
QList<QVariantMap> DataBaseModel::getLastQuery()
{
    return __lastQueryResult;
}

int DataBaseModel::getLastId()
{
    return __lastId;
}
DataBaseModel::~DataBaseModel()
{
    if(__db.open())
        __db.close();
}
