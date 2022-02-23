#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
#include<QSqlDatabase>
#include<QSqlQuery>

class OpeDB : public QObject
{
    Q_OBJECT
public:
    explicit OpeDB(QObject *parent = nullptr);
    static OpeDB& getInstance();
    void init();

signals:

private:
    QSqlDatabase m_db; //connect to database;

};

#endif // OPEDB_H
