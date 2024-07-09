#include "meteorologicalinformationinsert.h"
#include "ui_meteorologicalinformationinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
MeteorologicalInformationinsert::MeteorologicalInformationinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeteorologicalInformationinsert)
{
    ui->setupUi(this);
}

MeteorologicalInformationinsert::~MeteorologicalInformationinsert()
{
    delete ui;
}

void MeteorologicalInformationinsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO meteorologicalinformationinsert (InfoID, RecordingTime, Temperature, Rainfall, Humidity) VALUES (:InfoID, :RecordingTime, :Temperature, :Rainfall, :Humidity); ");
        query.prepare(sql);
        query.bindValue(":InfoID",ui->lineEdit->text());
        query.bindValue(":RecordingTime", ui->lineEdit_2->text());
        query.bindValue(":Temperature", ui->lineEdit_3->text());
        query.bindValue(":Rainfall", ui->lineEdit_4->text());
        query.bindValue(":Humidity", ui->lineEdit_5->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }

}

