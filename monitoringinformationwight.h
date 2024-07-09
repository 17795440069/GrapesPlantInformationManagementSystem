#ifndef MONITORINGINFORMATIONWIGHT_H
#define MONITORINGINFORMATIONWIGHT_H

#include <QWidget>

#include <QDebug>//用于在控制台输出调试信息
#include <QTimer>//定时器




namespace Ui {
class MonitoringInformationWight;
}

class MonitoringInformationWight : public QWidget
{
    Q_OBJECT

public:
    explicit MonitoringInformationWight(QWidget *parent = nullptr);
    ~MonitoringInformationWight();
public slots:
    void handleTimeout();
    void currectTime();

private:
    Ui::MonitoringInformationWight *ui;
    QTimer *m_pTimer;
    QTimer *timer;
};

#endif // MONITORINGINFORMATIONWIGHT_H
