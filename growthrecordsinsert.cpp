#include "growthrecordsinsert.h"
#include "ui_growthrecordsinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
GrowthRecordsinsert::GrowthRecordsinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrowthRecordsinsert)
{
    ui->setupUi(this);
}

GrowthRecordsinsert::~GrowthRecordsinsert()
{
    delete ui;
}

void GrowthRecordsinsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO growthrecords (RecordID, CropID, BaseID, GrowthPhase, RecordDate) VALUES (:RecordID, :CropID, :BaseID, :GrowthPhase, :RecordDate); ");
        query.prepare(sql);
        query.bindValue(":RecordID",ui->lineEdit->text());
        query.bindValue(":CropID", ui->lineEdit_2->text());
        query.bindValue(":BaseID", ui->lineEdit_3->text());
        query.bindValue(":GrowthPhase", ui->lineEdit_4->text());
        query.bindValue(":RecordDate", ui->lineEdit_5->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }

}

