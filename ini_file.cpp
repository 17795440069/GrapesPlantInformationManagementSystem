#include "ini_file.h"
#include <QtCore/QtCore>
#include <QFile>
#include <QDebug>

ini_file::ini_file()
{
    m_qstrFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
    qDebug()<<"m_qstrFileName: "<<m_qstrFileName;
    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);

    fileName = QCoreApplication::applicationDirPath() + "/Config_warn.ini";
    setting = new QSettings(fileName,QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));

}



ini_file::~ini_file()
{
    delete m_psetting;
    m_psetting = NULL;
}

//设置配置文件，用户名记忆
void ini_file::SetUsernameMemory(QString strUsernameMemery)
{
    m_psetting->setValue("/username/memory",strUsernameMemery);
}

//设置配置文件，用户名
void ini_file::SetUsername(QString strUsername)
{
    m_psetting->setValue("/username/username",strUsername);
}

//获取配置文件，用户名记忆状态
bool ini_file::GetUsernameMemory()
{
    if(m_psetting->value("/username/memory").toString()=="1"){
        return true;
    }else{
        return false;
    }
    //return m_psetting->value("/username/memory").toString();
}

//获取配置文件,用户名
QString ini_file::GetUsername()
{
    return m_psetting->value("/username/username").toString();
}

//设置配置文件，密码记忆
void ini_file::SetPasswordMemory(QString strPasswordMemery)
{
    m_psetting->setValue("/passdword/memory",strPasswordMemery);
}

//设置配置文件，密码
void ini_file::SetPassword(QString strPassword)
{
    m_psetting->setValue("/passdword/password",strPassword);
}

//获取配置文件，密码记忆状态
bool ini_file::GetPasswordMemory()
{
    if(m_psetting->value("/passdword/memory").toString()=="1"){
        return true;
    }else{
        return false;
    }
    //return m_psetting->value("/passdword/memory").toString();
}

//获取配置文件,用户名
QString ini_file::GetPassword()
{
    return m_psetting->value("/passdword/password").toString();
}

//保存串口配置
void ini_file::SetSerial(QString SerialName,QString baudRate,QString dataBit,QString stopBit,QString checkBit)
{
    m_psetting->setValue("/serialPort/serialName",SerialName);
    m_psetting->setValue("/serialPort/baudRate",baudRate);
    m_psetting->setValue("/serialPort/dataBit",dataBit);
    m_psetting->setValue("/serialPort/stopBit",stopBit);
    m_psetting->setValue("/serialPort/checkBit",checkBit);
}

//保存自动模式配置
void ini_file::SetAutomaticMode(int autoFan,int autoWaterPump,int autoHeat,int autolight)
{
    m_psetting->setValue("/automaticMode/fan",autoFan);
    m_psetting->setValue("/automaticMode/waterPump",autoWaterPump);
    m_psetting->setValue("/automaticMode/heat",autoHeat);
    m_psetting->setValue("/automaticMode/light",autolight);

}

//保存阈值配置
void ini_file::SetThresholdValue(QString airTempUp,QString airTempLow,QString humidityUp,QString humidityLow,QString soilHumidityUp,QString soilHumidityLow,QString lightIntensityHigh,QString lightIntensityLow)
{
    m_psetting->setValue("/thresholdValue/airTempUp",airTempUp);
    m_psetting->setValue("/thresholdValue/airTempLow",airTempLow);
    m_psetting->setValue("/thresholdValue/humidityUp",humidityUp);
    m_psetting->setValue("/thresholdValue/humidityLow",humidityLow);
    m_psetting->setValue("/thresholdValue/soilHumidityUp",soilHumidityUp);
    m_psetting->setValue("/thresholdValue/soilHumidityLow",soilHumidityLow);
    m_psetting->setValue("/thresholdValue/lightIntensityUp",lightIntensityHigh);
    m_psetting->setValue("/thresholdValue/lightIntensityLow",lightIntensityLow);
}
QStringList ini_file::GetSerial()
{
    QStringList serial;
    serial<<m_psetting->value("/serialPort/serialName").toString();
    serial<<m_psetting->value("/serialPort/baudRate").toString();
    serial<<m_psetting->value("/serialPort/dataBit").toString();
    serial<<m_psetting->value("/serialPort/stopBit").toString();
    serial<<m_psetting->value("/serialPort/checkBit").toString();
    return  serial;
}
int ini_file::GetAutoFan()
{
    return m_psetting->value("/automaticMode/fan").toInt();
}
int ini_file::GetAutoWaterPump()
{
    return m_psetting->value("/automaticMode/waterPump").toInt();
}
int ini_file::GetAutoHeat()
{
    return m_psetting->value("/automaticMode/heat").toInt();
}
int ini_file::GetAutolight()
{
    return m_psetting->value("/automaticMode/light").toInt();
}
QStringList ini_file::GetThresholdValue()
{
    QStringList thresholdValue;
    thresholdValue<<m_psetting->value("/thresholdValue/airTempUp").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/airTempLow").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/humidityUp").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/humidityLow").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/soilHumidityUp").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/soilHumidityLow").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/lightIntensityUp").toString();
    thresholdValue<<m_psetting->value("/thresholdValue/lightIntensityLow").toString();
    return thresholdValue;
}

int ini_file::getFirst()
{
    return m_psetting->value("/system/first").toInt();
}
void ini_file::setFirst(int a)
{
    m_psetting->setValue("/system/first",a);
}
QString ini_file::GetWarnText(QString month)
{
    int randomNumber = qrand() % 3 + 1;
    QString str = QString("/"+month+"/%1").arg(randomNumber);
    qDebug()<<str;
    qDebug()<<setting->value(str).toString();
    return setting->value(str).toString();
}
