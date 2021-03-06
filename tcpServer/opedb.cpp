#include "opedb.h"
#include<QDebug>
#include<QMessageBox>
OpeDB::OpeDB(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

OpeDB &OpeDB::getInstance()
{
    static OpeDB instance;
    return instance;
}

void OpeDB::init()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("/home/wjj/QtProjects/9/tcpServer/cloud.db");
    if(m_db.open()){
        QSqlQuery q;
        q.exec("select * from usrInfo");
        while(q.next()){
            int id = q.value(0).toInt();
            QString name = q.value(1).toString();
            int online = q.value(2).toInt();
            qDebug() << id << "|" << name <<
                        "|" << online;
        }


        m_db.close();
    }
    else{
        QMessageBox::critical(NULL, "waring", "open db failed");
    }
}

bool OpeDB::handleRegist(const char *name, const char *pwd)
{
    qDebug() << "Handling register...";
    if(name == NULL || pwd == NULL) return false;
    if(m_db.open()){
        QString sql = QString("insert into usrInfo(name, pwd) values(\'%1\',\'%2\');").arg(name).arg(pwd);
        QSqlQuery q;
        qDebug() << sql;
        return q.exec(sql);
    }
    else{
        QMessageBox::critical(NULL, "waring", "open db failed");
    }
    return false;

}





















