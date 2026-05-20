#include "optionwindow_v.h"

OptionWindow_V::OptionWindow_V(DataBaseModel* dbModel, QObject* parent)
    : QObject(parent), __dbModel(dbModel)
{
    if(!__dbModel->createDB())
    {
        qDebug() << "Ошибка создания базы";
        return;
    }
    __dbWay = __dbModel->getDbWay();

    if (!__dbWay.isEmpty() && !QFile::exists(__dbWay))
    {
        qWarning() << "Файл БД не найден по сохранённому пути:" << __dbWay;
        qWarning() << "Используем путь по умолчанию:";
        __dbWay = __defDbWay;
    }

    qDebug() << "База данных успешно инициализирована:" << __dbWay;
}
QString OptionWindow_V::saveDBWay(const QString& way)
{

    if( __dbWay != way)
    {
        if(__dbModel->setDatabasePath(way))
        return "";
      else
            return __dbModel->getLastError();
    }
    return "";
}

QString OptionWindow_V::getError()
{
    return __mess;
}
bool OptionWindow_V::saveDataFromXL(const QString& xlWay, const QString& dbWay)
{
    if(dbWay == "" || xlWay =="")
    {
        __mess = "Отсутсвие путей сохранения";
        return false;
    }
    __mess = "";
    if(! __xlmodel.saveData(xlWay))
    {
        __mess = "Ошибка чтения XL файла";
        return false;
    }
    if (__dbWay != dbWay)
    {
        __dbWay = dbWay;
        saveDBWay(dbWay);
    }
    QVector<XLData> buf = __xlmodel.getData();
    if (buf.size() == 0)
    {
        qDebug() << "Отсутствуют данные для сохранения;";
        return false;
    }
    int needcount = 200;
    QVector<QString> quer;
    for(int i = 0; i < buf.size(); ++i)
    {
        quer.clear();
        quer.append(buf[i].INN);
        quer.append(buf[i].Transaction);
        quer.append(buf[i].Sum);
        quer.append(buf[i].Appointment);
        quer.append(buf[i].Type);
        quer.append(buf[i].Subtype);
        quer.append(buf[i].Date);
        if(!__dbModel->insert("INSERT INTO Data (INN, Tranzaction, Sum, Appointment, Type, Subtype, Date) VALUES (?, ?, ?, ?, ?, ?, ?)", quer))
        {
            qDebug() << "Ошибка вставки данных:" << __dbModel->getLastError();
            break;
        }
        //if((i % needcount) == 0) progressUpdated(i, __length);
    }
    __mess = "";
    emit dataLoaded();
    return true;
}
bool OptionWindow_V::saveDataToXL(const QString& tabs, const QString& way)
{
    QVector<QString> tab;
    if (tabs.length() == 0) return false;
    tab = tabs.split(';', Qt::SkipEmptyParts);

    QString queryStr = "SELECT ";
    for (int i = 0; i < tab.size(); ++i)
    {
        if (i != 0) queryStr += ", ";
        queryStr += tab[i];
    }
    queryStr += " FROM Data";

    if (!__dbModel->select(queryStr))
    {
        qDebug() << "Ошибка выполнения запроса:" << __dbModel->lastError();
        return false;
    }

    if (__dbModel->getLastQuery().isEmpty())
    {
        qDebug() << "Результат запроса пуст!";
        return false;
    }

    bool saveResult = __xlmodel.saveToXml(tab, way, __dbModel->getLastQuery());

    if (!saveResult)
    {
        qDebug() << "Ошибка при сохранении данных в Excel/XML";
        return false;
    }
}

QString OptionWindow_V::getDbWay()
{
    return __dbWay;
}

