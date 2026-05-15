#include "optionwindow_v.h"

OptionWindow_V::OptionWindow_V(QObject *parent)
    : QObject(parent)
{

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TradeProject/TradeProject.db";
    __defDbWay = dbPath;

    QDir dir(QFileInfo(dbPath).absolutePath());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qCritical() << "Не удалось создать папку для БД:" << dir.absolutePath();
            return;
        }
    }
    if(! __createOptionTable(dbPath))
    {
        qWarning() << "Не получилось создать таблицу options";
        return;
    }


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "OptionWindowDB");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return;
    }
    QSqlQuery query(db);

    if (query.exec("SELECT DbWay FROM Options"))
    {
        if (query.next())
        {
            __dbWay = query.value(0).toString();
        } else
        {

            __dbWay = dbPath;
            query.prepare("INSERT INTO Options (DbWay) VALUES (?)");
            query.addBindValue(__dbWay);
            if (!query.exec()) {
                qWarning() << "Не удалось сохранить путь по умолчанию:" << query.lastError().text();
            }
        }
    }
    else
    {
        qWarning() << "Ошибка чтения DbWay из Options:" << query.lastError().text();
        __dbWay = dbPath;
    }

    if (!__dbWay.isEmpty() && !QFile::exists(__dbWay))
    {
        qWarning() << "Файл БД не найден по сохранённому пути:" << __dbWay;
        qWarning() << "Используем путь по умолчанию:" << dbPath;
        __dbWay = dbPath; // Фоллбэк
    }

    qDebug() << "База данных успешно инициализирована:" << __dbWay;
}
QString OptionWindow_V::saveDBWay(const QString& way)
{

    if( __dbWay != way)
    {
        const QString connectionName = "OptionWindowDBConnection";
        if (QSqlDatabase::contains(connectionName))
            QSqlDatabase::removeDatabase(connectionName);

        if(!__createOptionTable(way))
        {
            __mess = "Ошибка создания таблицы";
            return __mess;
        }
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(way);
        if (!db.open())
        {
            __mess = "Ошибка открытия базы:" + db.lastError().text();
            qDebug() << __mess;
            return __mess;
        }
        QSqlQuery query(db);
        query.prepare("UPDATE Options SET Dbway = ?");
        query.addBindValue(way);
        if (!query.exec())
        {
            __mess =  "Ошибка выполнения запроса:" + query.lastError().text();
            qDebug() << __mess;
            db.close();
            return __mess;
        }
        __saveNewWay(way);
        __dbWay = way;
        db.close();

    }
    return "";
}

QString OptionWindow_V::getError()
{
    return __mess;
}
bool OptionWindow_V::saveDataFromXL(const QString& xlWay, const QString& dbWay)
{
    __mess = "";
    if(! __xlmodel.saveData(xlWay))
    {
        __mess = "Ошибка чтения XL файла";
        return false;
    }
    if (__dbWay != dbWay)
        __dbWay = dbWay;

    if(! __xlmodel.loadData(dbWay))
    {
        __mess = "Ошибка загрузки данных в БД";
        return false;
    }
    __mess = "";
    return true;
}
bool OptionWindow_V::saveDataToXL(const QString& tabs, const QString& way)
{
   return __xlmodel.saveToXml(tabs,way,__dbWay);
}

bool OptionWindow_V::__createOptionTable(const QString& way)
{
    QSqlDatabase dbf = QSqlDatabase::addDatabase("QSQLITE", "OptionWindowDBcr");
    dbf.setDatabaseName(way);

    if (!dbf.open()) {
        qCritical() << "Ошибка открытия базы данных:" << dbf.lastError().text();
        return false;
    }
    QSqlQuery query(dbf);
    if (!query.exec("CREATE TABLE IF NOT EXISTS Options ("
                    "Theme STRING, "
                    "Dbway STRING UNIQUE)")) {
        qCritical() << "Ошибка создания таблицы Options:" << query.lastError().text();
        dbf.close();
        return false;
    }
    if(dbf.open())
        dbf.close();
    return true;
}

QString OptionWindow_V::getDbWay()
{
    return __dbWay;
}
void OptionWindow_V::__saveNewWay(const QString& newWay)
{
    QSqlDatabase dbf = QSqlDatabase::addDatabase("QSQLITE", "OptionWindowDBcr");
    dbf.setDatabaseName(__defDbWay);

    if (!dbf.open())
    {
        return;
    }
    QSqlQuery query(dbf);
    query.prepare("UPDATE Options SET Dbway = ?");
    query.addBindValue(newWay);
    if(!query.exec())
    {
        dbf.close();
        return;
    }
    if(dbf.open())
        dbf.close();
}
