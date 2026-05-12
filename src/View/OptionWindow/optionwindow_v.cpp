#include "optionwindow_v.h"

OptionWindow_V::OptionWindow_V()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DEF_WAY);
    if (!db.open())
    {
        qDebug() << "Ошибка открытия базы:" << db.lastError().text();
        __dbWay = "";
    }
    else
    {
        QSqlQuery query("SELECT DbWay FROM Options");
        if (!query.exec())
        {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            __dbWay = "";
        }
        else
        {
            __dbWay = query.value("Dbway").toString();
        }
        db.close();
    }

}
QString OptionWindow_V::saveDBWay(const QString& way)
{
    if( __dbWay != way)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(DEF_WAY);
        if (!db.open())
        {
            qDebug() << "Ошибка открытия базы:" << db.lastError().text();
            return "Ошибка открытия базы:" + db.lastError().text();
        }
         QSqlQuery query("UPDATE Options SET Dbway =" + way);
        if (!query.exec())
        {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return "Ошибка выполнения запроса:" + query.lastError().text();
        }
        __dbWay = way;
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
