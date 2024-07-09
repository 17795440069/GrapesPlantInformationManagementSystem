#include "informationwight.h"
#include "ui_informationwight.h"
#include "configwight.h"
#include "connection.h"
#include "plantinformationwight.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QJsonDocument>
#include "ini_file.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "connection.h"
#include "sharevar.h"
#include "monitoringinformationwight.h"
#include <QDateTime>
#include "sharevar.h"
InformationWight::InformationWight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationWight)
{

    ui->setupUi(this);
    sendNum = 0;
    recvNum = 0;
    serialaPort = new QSerialPort(this);
    connect(serialaPort,SIGNAL(readyRead()),this,SLOT(serialaPortReadyRead_Slot()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString month = curDateTime.toString ("MM");
    ui->label_2->setText(ini_file().GetWarnText(month));
    qDebug()<<month;
    ui->label_2->setWordWrap(true);
}
void InformationWight::timeUpdate()
{
    update_timer->stop();
    if(comData.length()!=0)
    {
        qDebug()<<comData;
    }
    comData.clear();
}
void InformationWight::serialaPortReadyRead_Slot()
{
    update_timer->start(100);//启动定时器，接收100毫秒数据（根据情况设定）
    comData.append(serialaPort->readAll());
//    comData = serialaPort->readAll();
    //统计接收的数据并显示
    recvNum+=comData.length();
    QString recvNum_str;
    recvNum_str.sprintf("%ld",recvNum);
    ui->label_recvNum->setText(recvNum_str);
    //qDebug()<<comData;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(comData,&error);

    if(error.error !=QJsonParseError::NoError)
    {
        //qDebug("josn error");
        return ;
    }

    QJsonObject obj = doc.object();
    //读取主控端温湿度
    QJsonValue master = obj.value("master");
    if(master.type()==QJsonValue::Object){
        QJsonObject master_obj = master.toObject();
        QString master_wendu = master_obj.value("temperature").toString();
        QString master_shidu = master_obj.value("humidness").toString();
        qDebug()<<"temperature:"<<master_wendu<<"   humidness:"<<master_shidu;
        gmaster_shidu = master_shidu;
        gmaster_wendu = master_wendu;
    }
    QJsonValue jiedian = obj.value("jiedian");
    if(jiedian.type()==QJsonValue::Object){
        QJsonObject jiedian_obj = jiedian.toObject();

        QString jiedian_soilHumidness = QString::number(jiedian_obj.value("so").toInt());
        QString jiedian_light = QString::number(jiedian_obj.value("li").toInt());
        QString jiedian_wendu = jiedian_obj.value("te").toString();
        QString jiedian_shidu = jiedian_obj.value("hu").toString();
        qDebug()<<"temperature:"<<jiedian_wendu<<"   humidness:"<<jiedian_shidu<<"   土壤湿度:"<<jiedian_soilHumidness<<"   光照强度:"<<jiedian_light;
        gjiedian_wendu = jiedian_wendu;
        gjiedian_shidu = jiedian_shidu;
        gjiedian_soil = jiedian_soilHumidness;
        gjiedian_light = jiedian_light;
    }
}
InformationWight::~InformationWight()
{
    delete ui;
}

void InformationWight::on_pushButton_4_clicked()
{
    configWight *cw = new configWight();
    cw->show();
}


void InformationWight::on_pushButton_2_clicked()
{
    plantinformationwight *pfw = new plantinformationwight();
    pfw->show();
}


void InformationWight::on_Bt_serialControl_clicked()
{
    if(ui->Bt_serialControl->text()=="打开"){
        QSerialPort::BaudRate baudRate;//波特率
        QSerialPort::DataBits dataBits;//数据位
        QSerialPort::StopBits stopBits;//停止位
        QSerialPort::Parity checkBits;//校验位
        QStringList serial = ini_file().GetSerial();
        qDebug()<<serial.at(1);
//QString::localeAwareCompare(serial.at(1),"115200") == 0
        if(serial.at(1)=="115200"){
            baudRate = QSerialPort::Baud115200;
        }else if(serial.at(1)=="9600"){
            baudRate = QSerialPort::Baud9600;
        }else if(serial.at(1)=="4800"){
            baudRate = QSerialPort::Baud4800;
        }

        if(serial.at(2)=="5"){
            dataBits = QSerialPort::Data5;
        }else if(serial.at(2)=="6"){
            dataBits = QSerialPort::Data6;
        }else if(serial.at(2)=="7"){
            dataBits = QSerialPort::Data7;
        }else if(serial.at(2)=="8"){
            dataBits = QSerialPort::Data8;
        }

        if(serial.at(3)=="1"){
            stopBits = QSerialPort::OneStop;
        }else if(serial.at(3)=="1.5"){
            stopBits = QSerialPort::OneAndHalfStop;
        }else if(serial.at(3)=="2"){
            stopBits = QSerialPort::TwoStop;
        }

        if(serial.at(4)=="none"){
            checkBits = QSerialPort::NoParity;
        }

        serialaPort->setPortName(serial.at(0));
        serialaPort->setBaudRate(baudRate);
        serialaPort->setDataBits(dataBits);
        serialaPort->setStopBits(stopBits);
        serialaPort->setParity(checkBits);

        if(serialaPort->open(QIODevice::ReadWrite)== true){
    //        QMessageBox::information(this,"提示","成功！");
            ui->Bt_serialControl->setText("关闭");
            ui->lable_getInforStatus->setText("获取信息状态： 正常");
            ui->lable_getInforStatus->setStyleSheet("color:green;");
        }else{
            QMessageBox::critical(this,"提示","失败！");
        }
    }else{
        serialaPort->close();
        ui->Bt_serialControl->setText("打开");
        ui->lable_getInforStatus->setText("获取信息状态： 关闭");
        ui->lable_getInforStatus->setStyleSheet("color:black;");
    }
}


void InformationWight::on_pushButton_clicked()
{
    MonitoringInformationWight *i=new MonitoringInformationWight();
    i->show();
}

void InformationWight::read_data(QNetworkReply *reply){
    QByteArray array = reply->readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array,&error);

    if(error.error !=QJsonParseError::NoError)
    {
        qDebug("josn error");
        return ;
    }
    QJsonObject obj = doc.object();
    //时间
    QString time = obj.value("time").toString();
    time = time.mid(5,5);
    qDebug()<<time;

    //地区
    QJsonObject cityobj = obj.value("cityInfo").toObject();
//    QString city = cityobj.value("city").toString();
    QJsonObject dataobj = obj.value("data").toObject();
    //今日温度
    QString wendu = dataobj.value("wendu").toString();
    ui->Edit_todayTemp->setText(wendu+"℃");
    //今日湿度
    QString shidu = dataobj.value("shidu").toString();
    ui->Edit_todayShidu->setText(shidu);
    //今日PM2.5
    int PM25 = dataobj.value("pm25").toInt();
    QString pm25 = QString::number(PM25);
    ui->Edit_todayPM25->setText(pm25);
    //空气质量
    QString quality = dataobj.value("quality").toString();
    ui->Edit_todayKQZL->setText(quality);
    //近一周的天气
    QJsonArray forecast_array = dataobj.value("forecast").toArray();
    QJsonObject weatherobj = forecast_array.at(0).toObject();
    //最高温度
    QString high = weatherobj.value("high").toString();
    high = high.mid(3);
    ui->Edit_oneDayHightTemp->setText(high);
    //最低温度
    QString low = weatherobj.value("low").toString();
    low = low.mid(3);
    ui->Edit_oneDayLowTemp->setText(low);
    //天气
    QString type = weatherobj.value("type").toString();
    ui->Edit_oneDayWeather->setText(type);
    //日期
    QString ymd = weatherobj.value("ymd").toString();
    ui->Edit_oneDayDate->setText(ymd);
    //风
    QString fx = weatherobj.value("fx").toString();
    QString fl = weatherobj.value("fl").toString();
    QString wind = fx+fl;
    ui->Edit_oneDayFl->setText(wind);
    //空气质量
    int aqii = weatherobj.value("aqi").toInt();
    QString aq = QString::number(aqii);
    ui->Edit_oneDayKQZS->setText(aq);

    //-------------------------
    weatherobj = forecast_array.at(1).toObject();
    //最高温度
    high = weatherobj.value("high").toString();
    high = high.mid(3);
    ui->Edit_twoDayHightTemp->setText(high);
    //最低温度
    low = weatherobj.value("low").toString();
    low = low.mid(3);
    ui->Edit_twoDayLowTemp->setText(low);
    //天气
    type = weatherobj.value("type").toString();
    ui->Edit_twoDayWeather->setText(type);
    //日期
    ymd = weatherobj.value("ymd").toString();
    ui->Edit_twoDayDate->setText(ymd);
    //风
    fx = weatherobj.value("fx").toString();
    fl = weatherobj.value("fl").toString();
    wind = fx+fl;
    ui->Edit_twoDayFl->setText(wind);
    //空气质量
    aqii = weatherobj.value("aqi").toInt();
    aq = QString::number(aqii);
    ui->Edit_twoDayKQZS->setText(aq);
}

void InformationWight::on_Cb_cityId_currentIndexChanged(const QString &arg1)
{
    QString a = arg1;
    //天气url
    QString cituId ="http://t.weather.sojson.com/api/weather/city/" + ui->Cb_cityId->currentText();
    QUrl url(cituId);
    //创建一个请求对象
    QNetworkRequest request(url);
    manager.get(request);
    //关联finished信号
    connect(&manager,&QNetworkAccessManager::finished,this,&InformationWight::read_data);
}

