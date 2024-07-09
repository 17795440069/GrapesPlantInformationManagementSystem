#ifndef INFORMATIONWIGHT_H
#define INFORMATIONWIGHT_H

#include <QWidget>
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
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "connection.h"
namespace Ui {
class InformationWight;
}

class InformationWight : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWight(QWidget *parent = nullptr);
    ~InformationWight();

    QByteArray comData;
    QTimer *update_timer = new QTimer();
    QTimer *apc220_update_timer = new QTimer();


private slots:
    void on_pushButton_4_clicked();
    void read_data(QNetworkReply *reply);
    void on_pushButton_2_clicked();

    void on_Bt_serialControl_clicked();

//    void serialaPort_send(QString key,int value);
    void serialaPortReadyRead_Slot();
    void timeUpdate();
//    void read_data(QNetworkReply *reply);
//    void apc220_updata();

    void on_pushButton_clicked();

    void on_Cb_cityId_currentIndexChanged(const QString &arg1);

private:
    Ui::InformationWight *ui;
    long sendNum,recvNum;
    QNetworkAccessManager manager;
    QTimer mtimer;
};

#endif // INFORMATIONWIGHT_H
