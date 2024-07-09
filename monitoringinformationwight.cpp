#include "monitoringinformationwight.h"
#include "ui_monitoringinformationwight.h"
#include "sharevar.h"
#include <time.h>
#include <QDateTime>
MonitoringInformationWight::MonitoringInformationWight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitoringInformationWight)
{
    ui->setupUi(this);
    m_pTimer = new QTimer(this);
    timer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(timer, SIGNAL(timeout()), this, SLOT(currectTime()));
    m_pTimer->start(5000);
    timer->start(1000);
}

MonitoringInformationWight::~MonitoringInformationWight()
{
    delete ui;
}
void MonitoringInformationWight::handleTimeout()
 {
     ui->lineEdit->setText(gmaster_wendu+"℃");
     ui->lineEdit_2->setText(gmaster_shidu+"%");
     ui->lineEdit_3->setText(gjiedian_wendu+"℃");
     ui->lineEdit_4->setText(gjiedian_shidu+"%");
     ui->lineEdit_9->setText(gjiedian_light+"Lux");
     double soil = gjiedian_soil.toDouble();
     soil = soil/10.0;
     gjiedian_soil = QString::number(soil);
     ui->lineEdit_10->setText(gjiedian_soil+"%");

 }
void MonitoringInformationWight::currectTime()
{
    QDateTime curDateTime=QDateTime::currentDateTime();

    ui->lineEdit_11->setText(curDateTime.toString ("hh:mm:ss"));
}

