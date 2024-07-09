#ifndef INI_FILE_H
#define INI_FILE_H

#include <QString>
#include <QSettings>

class ini_file
{
public:
    ini_file();
    virtual ~ini_file();
    void CreateFile(QString qstrFilePath, QString qstrFileName);
    void SetUsernameMemory(QString strUsernameMemery);//
    void SetUsername(QString strUsername);
    bool GetUsernameMemory();
    QString GetUsername();
    void SetPasswordMemory(QString strPasswordMemery);//
    void SetPassword(QString strPassword);
    bool GetPasswordMemory();
    QString GetPassword();
    void SetSerial(QString SerialName,QString baudRate,QString dataBit,QString stopBit,QString checkBit);
    void SetAutomaticMode(int autoFan,int autoWaterPump,int autoHeat,int autolight);
    void SetThresholdValue(QString airTempUp,QString airTempLow,QString humidityUp,QString humidityLow,QString soilHumidityUp,QString soilHumidityLow,QString lightIntensityHigh,QString lightIntensityLow);
    QStringList GetSerial();
    int GetAutoFan();
    int GetAutoWaterPump();
    int GetAutoHeat();
    int GetAutolight();
    QStringList GetThresholdValue();
    int getFirst();
    void setFirst(int a);
    QString GetWarnText(QString month);
private:
    QString m_qstrFileName;
    QSettings *m_psetting;
    QString fileName;
    QSettings *setting;
};

#endif // INI_FILE_H


