#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QJsonDocument>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    sendNum = 0;
    recvNum = 0;
    ui->setupUi(this);
//    QPalette pal = this->palette();
//    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/1.png").scaled(this->size())));
//    setPalette(pal);
    QStringList serialPortName;
    serialaPort = new QSerialPort(this);
    connect(serialaPort,SIGNAL(readyRead()),this,SLOT(serialaPortReadyRead_Slot()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(apc220_update_timer, SIGNAL(timeout()), this, SLOT(apc220_updata()));
    apc220_update_timer->setInterval(100000);
    apc220_update_timer->start();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        serialPortName<<info.portName();
    }
    ui->serialCb->addItems(serialPortName);
    on_Cb_cityId_currentIndexChanged("101170101");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::serialaPortReadyRead_Slot()
{

    update_timer->start(100);//启动定时器，接收100毫秒数据（根据情况设定）
    comData.append(serialaPort->readAll());
//    comData = serialaPort->readAll();
    //统计接收的数据并显示
    recvNum+=comData.length();
    QString recvNum_str;
    recvNum_str.sprintf("%ld",recvNum);
    ui->label_recvNum->setText(recvNum_str);


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
        ui->Edit_masterTemp->setText(master_wendu+"℃");
        ui->Edit_masterHumidity->setText(master_shidu+"%");
    }
    QJsonValue jiedian = obj.value("jiedian");
    if(jiedian.type()==QJsonValue::Object){
        QJsonObject jiedian_obj = jiedian.toObject();

        QString jiedian_soilHumidness = QString::number(jiedian_obj.value("so").toInt());
        QString jiedian_light = QString::number(jiedian_obj.value("li").toInt());
        QString jiedian_wendu = jiedian_obj.value("te").toString();
        QString jiedian_shidu = jiedian_obj.value("hu").toString();
        ui->Edit_jiedianSoilHumditness->setText(jiedian_soilHumidness);
        ui->Edit_jiedianLight->setText(jiedian_light+"lux");
        ui->Edit_jiedianTemp->setText(jiedian_wendu+"℃");
        ui->Edit_jiedianHumditness->setText(jiedian_shidu+"%");

    }


}

void MainWindow::on_Bt_serialControl_clicked()
{
    if(ui->Bt_serialControl->text()=="打开"){
        QSerialPort::BaudRate baudRate;//波特率
        QSerialPort::DataBits dataBits;//数据位
        QSerialPort::StopBits stopBits;//停止位
        QSerialPort::Parity checkBits;//校验位


        if(ui->baundrateCb->currentText()=="115200"){
            baudRate = QSerialPort::Baud115200;
        }else if(ui->baundrateCb->currentText()=="9600"){
            baudRate = QSerialPort::Baud9600;
        }else if(ui->baundrateCb->currentText()=="4800"){
            baudRate = QSerialPort::Baud4800;
        }

        if(ui->dateCb->currentText()=="5"){
            dataBits = QSerialPort::Data5;
        }else if(ui->dateCb->currentText()=="6"){
            dataBits = QSerialPort::Data6;
        }else if(ui->dateCb->currentText()=="7"){
            dataBits = QSerialPort::Data7;
        }else if(ui->dateCb->currentText()=="8"){
            dataBits = QSerialPort::Data8;
        }

        if(ui->stopCb->currentText()=="1"){
            stopBits = QSerialPort::OneStop;
        }else if(ui->stopCb->currentText()=="1.5"){
            stopBits = QSerialPort::OneAndHalfStop;
        }else if(ui->stopCb->currentText()=="2"){
            stopBits = QSerialPort::TwoStop;
        }

        if(ui->checkCb->currentText()=="none"){
            checkBits = QSerialPort::NoParity;
        }

        serialaPort->setPortName(ui->serialCb->currentText());
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

void MainWindow::on_Cb_cityId_currentIndexChanged(const QString &arg1)
{
    QString a = arg1;
    //天气url
    QString cituId ="http://t.weather.sojson.com/api/weather/city/" + ui->Cb_cityId->currentText();
    QUrl url(cituId);
    //创建一个请求对象
    QNetworkRequest request(url);
    manager.get(request);
    //关联finished信号
    connect(&manager,&QNetworkAccessManager::finished,this,&MainWindow::read_data);
}
void MainWindow::read_data(QNetworkReply *reply){
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
void MainWindow::timeUpdate()
{
    update_timer->stop();
    if(comData.length()!=0)
    {
        qDebug()<<comData;
    }
    comData.clear();
}
void MainWindow::on_Bt_fillInLight_clicked()
{
    if(ui->Bt_fillInLight->text()=="补光:开启"){
        ui->Bt_fillInLight->setText("补光:关闭");
        serialaPort_send("light",0);
        //serialaPort->write("{\"light\":0}");
    }else{
        ui->Bt_fillInLight->setText("补光:开启");
//        serialaPort_send("light",1);
        serialaPort->write("{\"light\":1}");
    }
}
void MainWindow::on_Bt_waterPump_clicked()
{
//    if(ui->Bt_waterPump->text()=="水泵:开启"){
//        ui->Bt_waterPump->setText("水泵:关闭");
//        serialaPort_send("water",1);
//    }else{
//        ui->Bt_waterPump->setText("水泵:开启");
//        serialaPort_send("water",0);
//    }
    if(ui->Bt_waterPump->text()=="水泵:开启"){
        ui->Bt_waterPump->setText("水泵:关闭");
        serialaPort_send("alarm",0);
    }else{
        ui->Bt_waterPump->setText("水泵:开启");
        serialaPort_send("alarm",1);
    }
}
void MainWindow::on_Bt_heat_clicked()
{
    if(ui->Bt_heat->text()=="加热:开启"){
        ui->Bt_heat->setText("加热:关闭");
        serialaPort_send("heat",0);
    }else{
        ui->Bt_heat->setText("加热:开启");
        serialaPort_send("heat",1);
    }
}
void MainWindow::on_Bt_fan_clicked()
{
    if(ui->Bt_fan->text()=="风扇:开启"){
        ui->Bt_fan->setText("风扇:关闭");
        serialaPort_send("fan",1);
    }else{
        ui->Bt_fan->setText("风扇:开启");
        serialaPort_send("fan",0);
    }
}
void MainWindow::on_Bt_autoMode_clicked()
{
    if(ui->Bt_autoMode->text()=="自动模式:开启"){
        ui->Bt_autoMode->setText("自动模式:关闭");
    }else{
        ui->Bt_autoMode->setText("自动模式:开启");
    }
}
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
void MainWindow::apc220_updata()
{

}
void MainWindow::serialaPort_send(QString key,int value){
    QJsonObject json;
    QString val_str = QString::number(value);
    json.insert(key, val_str);

    // 构建 JSON 文档
    QJsonDocument jsonDocument;
    jsonDocument.setObject(json);

    QByteArray jsonString = jsonDocument.toJson(QJsonDocument::Indented);
    QString senddata = QString(jsonString);
    serialaPort->write(jsonString);
    sendNum+=jsonString.size();
    QString sendString = QString::number(sendNum);
    ui->label_sendNum->setText(sendString);
    qDebug() << jsonString;
}
