#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QLabel>
#include <QTimer>
#include <QTime>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *serialaPort;
    QByteArray comData;
    QTimer *update_timer = new QTimer();
    QTimer *apc220_update_timer = new QTimer();


private slots:
    void read_data(QNetworkReply *reply);
    void on_Bt_serialControl_clicked();
    void serialaPortReadyRead_Slot();
    void on_Cb_cityId_currentIndexChanged(const QString &arg1);
    void timeUpdate();
    void on_Bt_fillInLight_clicked();
    void on_Bt_waterPump_clicked();
    void on_Bt_heat_clicked();
    void on_Bt_fan_clicked();
    void on_Bt_autoMode_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void apc220_updata();
    void serialaPort_send(QString key,int value);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QTimer mtimer;
    long sendNum,recvNum;
};
#endif // MAINWINDOW_H
