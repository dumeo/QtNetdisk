#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadConfig();
public slots:
    void showConnect();
    void recvMsg();
    void offline();

private slots:
    void on_login_bt_clicked();

    void on_regist_bt_clicked();

    void on_cancel_bt_clicked();

private:
    Ui::MainWindow *ui;
    QString m_strIP;
    quint16 m_usPort;
    QTcpSocket m_tcpSocket;
};
#endif // MAINWINDOW_H
