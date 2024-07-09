#include "configwight.h"
#include "ui_configwight.h"
#include "ini_file.h"
#include <QDebug>
#include "informationwight.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QJsonDocument>
#include "sharevar.h"
configWight::configWight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configWight)
{
    ui->setupUi(this);
    try {
        //获取主机串口名称
        QStringList serialPortName;
        //serialaPort = new QSerialPort(this);
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
            serialPortName<<info.portName();
        }

        ui->serialCb->addItems(serialPortName);

        QStringList serial = ini_file().GetSerial();
        //串口配置
        if(serial.at(0)!=""){
            ui->serialCb->setCurrentText(serial.at(0));
        }
        ui->baundrateCb->setCurrentText(serial.at(1));
        ui->dateCb->setCurrentText(serial.at(2));
        ui->stopCb->setCurrentText(serial.at(3));
        ui->checkCb->setCurrentText(serial.at(4));
        //自动模式配置

        ui->checkBox->setChecked(ini_file().GetAutoFan());
        ui->checkBox_2->setChecked(ini_file().GetAutoWaterPump());
        ui->checkBox_3->setChecked(ini_file().GetAutoHeat());
        ui->checkBox_4->setChecked(ini_file().GetAutolight());

        //阈值配置
        QStringList threshold = ini_file().GetThresholdValue();

        ui->Edit_tempThresholdHigh->setText(threshold.at(0));
        ui->Edit_tempThresholdLow->setText(threshold.at(1));
        ui->Edit_humidityThresholdHigh->setText(threshold.at(2));
        ui->Edit_humidityThresholdLow->setText(threshold.at(3));
        ui->Edit_soilHumidityThresholdHigh->setText(threshold.at(4));
        ui->Edit_soilHumidityThresholdLow->setText(threshold.at(5));
        ui->Edit_lightIntensityHigh->setText(threshold.at(6));
        ui->Edit_lightIntensityLow->setText(threshold.at(7));
    }  catch (...) {
        qDebug()<< "捕获到异常";
    }



}

configWight::~configWight()
{
    delete ui;
}

//保存按钮被点击
void configWight::on_pushButton_clicked()
{
    //串口配置
    QString serialPort = ui->serialCb->currentText();
    QString baudRate = ui->baundrateCb->currentText();
    QString dataBit = ui->dateCb->currentText();
    QString stopBit = ui->stopCb->currentText();
    QString checkBit = ui->checkCb->currentText();
    ini_file().SetSerial(serialPort,baudRate,dataBit,stopBit,checkBit);
    //自动模式配置
    int fan_cb = ui->checkBox->isChecked();
    int waterPump_cb = ui->checkBox_2->isChecked();
    int heat_cb = ui->checkBox_3->isChecked();
    int light_cb = ui->checkBox_4->isChecked();
    ini_file().SetAutomaticMode(fan_cb,waterPump_cb,heat_cb,light_cb);
    //阈值配置
    QString airTempUp=ui->Edit_tempThresholdHigh->text();
    QString airTempLow=ui->Edit_tempThresholdLow->text();
    QString humidityUp=ui->Edit_humidityThresholdHigh->text();
    QString humidityLow=ui->Edit_humidityThresholdLow->text();
    QString soilHumidityUp=ui->Edit_soilHumidityThresholdHigh->text();
    QString soilHumidityLow=ui->Edit_soilHumidityThresholdLow->text();
    QString lightIntensityHigh=ui->Edit_lightIntensityHigh->text();
    QString lightIntensityLow=ui->Edit_lightIntensityLow->text();
    ini_file().SetThresholdValue(airTempUp,airTempLow,humidityUp,humidityLow,soilHumidityUp,soilHumidityLow,lightIntensityHigh,lightIntensityLow);

    bool first = ini_file().getFirst();
    if(first){
        ini_file().setFirst(0);
        InformationWight *i = new InformationWight();
        i->show();
        close();
    }
}


void configWight::on_pushButton_4_clicked()
{
    close();
}


void configWight::on_Bt_fillInLight_clicked()
{
    if(ui->Bt_fillInLight->text()=="补光:开启"){
        ui->Bt_fillInLight->setText("补光:关闭");
        serialaPort_send("light",0);
        //serialaPort->write("{\"light\":0}");
    }else{
        ui->Bt_fillInLight->setText("补光:开启");
        serialaPort_send("light",1);
        //serialaPort->write("{\"light\":1}");
    }
}


void configWight::on_Bt_waterPump_clicked()
{
    if(ui->Bt_waterPump->text()=="水泵:开启"){
        ui->Bt_waterPump->setText("水泵:关闭");
        serialaPort_send("alarm",0);
    }else{
        ui->Bt_waterPump->setText("水泵:开启");
        serialaPort_send("alarm",1);
    }
}


void configWight::on_Bt_heat_clicked()
{
    if(ui->Bt_heat->text()=="加热:开启"){
        ui->Bt_heat->setText("加热:关闭");
        serialaPort_send("heat",0);
    }else{
        ui->Bt_heat->setText("加热:开启");
        serialaPort_send("heat",1);
    }
}


void configWight::on_Bt_fan_clicked()
{
    if(ui->Bt_fan->text()=="风扇:开启"){
        ui->Bt_fan->setText("风扇:关闭");
        serialaPort_send("fan",1);
    }else{
        ui->Bt_fan->setText("风扇:开启");
        serialaPort_send("fan",0);
    }
}


void configWight::on_Bt_autoMode_clicked()
{
    if(ui->Bt_autoMode->text()=="自动模式:开启"){
        ui->Bt_autoMode->setText("自动模式:关闭");
    }else{
        ui->Bt_autoMode->setText("自动模式:开启");
    }
}

void configWight::serialaPort_send(QString a,int b)
{
    QString all = "{\""+a+"\":\""+QString::number(b)+"\"}";
    //QString al = "{\"light\":\"1\"}";
    qDebug()<<"发送数据为:"<<all;
//    QJsonObject interestObj;
    // 插入元素，对应键值对
//    interestObj.insert(a, QString::number(b));
    int res = -1;
    res = serialaPort->write(all.toLatin1());
    if(res == -1){// 发送失败
        qDebug()<<"send failed";
    }else{
        qDebug()<<"send success";
    }
//    QJsonDocument document;
//    document.setObject(interestObj);
//    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
//    //QString strJson(byteArray);

//    serialaPort->write(document.toJson());
//    qDebug()<<document.toJson();
}

void configWight::on_Bt_tempThresholdSet_clicked()
{
    on_pushButton_clicked();
}


void configWight::on_Bt_humidityThresholdSet_clicked()
{
    on_pushButton_clicked();
}


void configWight::on_Bt_soilHumidityThresholdSet_clicked()
{
    on_pushButton_clicked();
}


void configWight::on_Bt_lightIntensitySet_clicked()
{
    on_pushButton_clicked();
}

