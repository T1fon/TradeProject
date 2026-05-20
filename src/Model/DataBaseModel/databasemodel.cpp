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
        if(!insert("INSERT INTO Options (DbWay) VALUES (?)",params))
        {
            return;
        }
    }
    else
    {
        if(select("SELECT DbWay from Options"))
        {
            if(__pathDB != __lastQueryResult.at(0))
            {
                if(!setDatabasePath(__lastQueryResult.at(0).toString()))
                {
                    qDebug() << "Не удалось изменить путь к Базе. Испоьзуется стандратный";
                }
            }
        }
    }
}

bool DataBaseModel::setDatabasePath(const QString& path)
{
    if(__db.open())
        __db.close();
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
    return true;
}
bool DataBaseModel::select(const QString& query)
{
    QSqlQuery qu;
    qu.prepare(query);
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

    QString query = "BEGIN TRANSACTION;"
                    "CREATE TABLE IF NOT EXIST Contr_question "
                    "("
                    "id  INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "Question INTEGER,"
                    "Answer STRING"
                    ");"

                    "CREATE TABLE IF NOT EXIST Login "
                    "("
                    "id  INTEGER  PRIMARY KEY AUTOINCREMENT,"
                    "Password  STRING (30)  NOT NULL  UNIQUE,"
                    "Name  INTEGER (30) NOT NULL  UNIQUE,"
                    "lvl   INTEGER (1)  NOT NULL  DEFAULT (0),"
                    "Question INTEGER  REFERENCES contr_question (id)"
                    ");"

                    "CREATE TABLE IF NOT EXIST Login "
                    "("
                    "Id  INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "Name  STRING  NOT NULL,"
                    "Surname  STRING,"
                    "Login_id INTEGER REFERENCES Login (id),"
                    "Img  STRING"
                    ");"

                    "CREATE TABLE IF NOT EXIST Client "
                    "("
                    "Id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "Name STRING  NOT NULL,"
                    "Phones  STRING,"
                    "INN     STRING,"
                    "Login_id INTEGER REFERENCES Login (id) NOT NULL,"
                    "Manager_id INTEGER REFERENCES Manager (Id),"
                    "Img  STRING,"
                    ");"

                    "CREATE TABLE IF NOT EXIST Counter_manager "
                    "("
                    "contr_id  INTEGER REFERENCES Client (Id),"
                    "data_id INTEGER REFERENCES Data (Id)"
                    ");"

                    "CREATE TABLE IF NOT EXIST counter_client "
                    "("
                    "counter_id INTEGER REFERENCES Counterparty (id),"
                    "Client_id  INTEGER REFERENCES Client (Id) "
                    ");"

                    "CREATE TABLE IF NOT EXIST Counter_client "
                    "("
                    "counter_id INTEGER REFERENCES Counterparty (id),"
                    "Client_id  INTEGER REFERENCES Client (Id) "
                    ");";

    if(!request(query))
    {
        qDebug() << __lastError;
        return false;
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

DataBaseModel::~DataBaseModel()
{
    if(__db.open())
        __db.close();
}
