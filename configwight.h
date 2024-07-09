#ifndef CONFIGWIGHT_H
#define CONFIGWIGHT_H

#include <QWidget>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QJsonDocument>
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
namespace Ui {
class configWight;
}

class configWight : public QWidget
{
    Q_OBJECT

public:
    explicit configWight(QWidget *parent = nullptr);
    ~configWight();
    //QSerialPort *serialaPort;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_Bt_fillInLight_clicked();

    void on_Bt_waterPump_clicked();

    void on_Bt_heat_clicked();

    void on_Bt_fan_clicked();

    void on_Bt_autoMode_clicked();
    void serialaPort_send(QString a,int b);

    void on_Bt_tempThresholdSet_clicked();

    void on_Bt_humidityThresholdSet_clicked();

    void on_Bt_soilHumidityThresholdSet_clicked();

    void on_Bt_lightIntensitySet_clicked();

private:
    Ui::configWight *ui;
};

#endif // CONFIGWIGHT_H
