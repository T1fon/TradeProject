#pragma once

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QSqlRecord>

class DataBaseModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit DataBaseModel(QObject *parent = nullptr);
    ~DataBaseModel();

    bool setDatabasePath(const QString& path);
    void setMainTable();
    QString getLastError();
    QString getDbWay();
    QList<QVariantMap> getLastQuery();

    bool request(const QString& query);
    bool insert(const QString& query, const QVector<QString>& params);
    bool select(const QString& query);
    bool createDB();

private:
    QSqlDatabase __db;
    QList<QVariantMap> __lastQueryResult;

    QString __pathDB;
    QString __responce;
    QString __lastError;
    QString __standartPatt = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TradeProject/TradeProject.db";
};
