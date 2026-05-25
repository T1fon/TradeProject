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
bool OptionWindow_V::saveDataFromXL(const QString& xlWay, const QString& dbWay, const QString& clientId)
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

    if (!__processCounterparties(clientId)) return false;

    if (!__processTransactions()) return false;

    return true;

    /*QVector<XLData> buf = __xlmodel.getData();


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
        quer.append(buf[i].Transaction);
        quer.append(buf[i].Sum);
        quer.append(buf[i].Appointment);
        quer.append(buf[i].Type);
        quer.append(buf[i].Subtype);
        quer.append(buf[i].Date);
        if(!__dbModel->insert("INSERT INTO Data (Tranzaction, Sum, Appointment, Type, Subtype, Date) VALUES (?, ?, ?, ?, ?, ?, ?)", quer))
        {
            qDebug() << "Ошибка вставки данных:" << __dbModel->getLastError();
            break;
        }
        //if((i % needcount) == 0) progressUpdated(i, __length);
    }
    __mess = "";
    emit dataLoaded();
    return true;*/
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
    return true;
}
bool OptionWindow_V::__processCounterparties(const QString& clientId)
{
    QMap<QString, int> counterpartyIdMap;

    QString queryExisting = "SELECT INN, id FROM Counterparty";
    if (!__dbModel->select(queryExisting))
    {
        qDebug() << "[OPTION_ERROR] Ошибка при получении контрагентов:" << __dbModel->lastError();
        return false;
    }

    for (const auto& row : __dbModel->getLastQuery())
        counterpartyIdMap[row["INN"].toString()] = row["id"].toInt();

    for (const auto& record : __xlmodel.getData())
    {
        QString inn = record.INN;

        if (inn != "" && !counterpartyIdMap.contains(inn))
        {
            QString queryInsert = "INSERT INTO Counterparty (Name, INN, Client_id) VALUES (?, ?, ?)";
            QVector<QString> params = {record.Name, inn, clientId};

            if (!__dbModel->insert(queryInsert, params))
            {
                qDebug() << "[OPTION_ERROR] Ошибка вставки контрагента:" << __dbModel->lastError();
                return false;
            }

            if (__dbModel->select("SELECT id FROM Counterparty WHERE INN = '" + inn + "'"))
            {
                const QVector<QVariantMap>& queryResult = __dbModel->getLastQuery();
                if (!queryResult.isEmpty())
                {
                    const QVariantMap& record = queryResult.first();
                    if (!counterpartyIdMap.contains(inn))
                    {
                        counterpartyIdMap[inn] = record.value("id").toInt();
                    }
                }
            } else
            {
                qDebug() << "[OPTION_ERROR] Ошибка при SELECT после INSERT:" << __dbModel->lastError();
                return false;
            }
        }
    }

    return true;
}

bool OptionWindow_V::__processTransactions()
{
    QMap<QString, QMap<QString, int>> transactionIdMap;

    QString queryExisting = R"(
        SELECT
            d.Tranzaction,
            d.Date,
            d.id AS data_id,
            c.INN,
            cd.counter_id
        FROM Data d
        JOIN Counter_data cd ON d.id = cd.data_id
        JOIN Counterparty c ON cd.counter_id = c.id
    )";

    if (!__dbModel->select(queryExisting)) {
        qDebug() << "[OPTION_ERROR] Ошибка при получении транзакций:" << __dbModel->lastError();
        return false;
    }

    const QList<QVariantMap>& results = __dbModel->getLastQuery();

    for (const QVariantMap& row : results)
    {
        QString inn = row.value("INN").toString();
        QString transaction = row.value("Tranzaction").toString() + "_" + row.value("Date").toString();
        int id = row.value("data_id").toInt();

        transactionIdMap[inn][transaction] = id;
    }

    for (const auto& record : __xlmodel.getData())
    {
        QString inn = record.INN;
        QString transactionKey = record.Transaction + "_" + record.Date;
        if (!transactionIdMap[inn].contains(transactionKey))
        {
            QString queryInsertData = R"(
                INSERT INTO Data (Tranzaction, Sum, Appointment, Type, Subtype, Date)
                VALUES (?, ?, ?, ?, ?, ?)
            )";
            QVector<QString> dataParams =
                {
                record.Transaction,
                record.Sum,
                record.Appointment,
                record.Type,
                record.Subtype,
                record.Date
            };

            if (!__dbModel->insert(queryInsertData, dataParams))
            {
                qDebug() << "[ERROR] Ошибка вставки транзакции:" << __dbModel->lastError();
                return false;
            }

            int dataId = __dbModel->getLastId();
            int countId;
            if(__dbModel->select("SELECT id FROM Counterparty WHERE INN = " + inn))
            {
                const QVector<QVariantMap>& queryResult = __dbModel->getLastQuery();
                if (!queryResult.isEmpty())
                {
                    const QVariantMap& record = queryResult.first();
                    countId = record.value("id").toInt();
                }
            }

            QString queryLink = "INSERT INTO Counter_data (counter_id, data_id) VALUES (?, ?)";
            QVector<int> linkParams = {
                countId,
                dataId
            };

            if (!__dbModel->insert(queryLink, linkParams)) {
                qDebug() << "[ERROR] Ошибка связи транзакции с контрагентом:" << __dbModel->lastError();
                return false;
            }

            // Обновляем карту ID транзакций
            transactionIdMap[inn][transactionKey] = dataId;
        }
    }

    return true;
}

QString OptionWindow_V::getDbWay()
{
    return __dbWay;
}

