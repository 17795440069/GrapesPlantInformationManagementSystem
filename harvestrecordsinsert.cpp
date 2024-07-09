#include "harvestrecordsinsert.h"
#include "ui_harvestrecordsinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
HarvestRecordsinsert::HarvestRecordsinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HarvestRecordsinsert)
{
    ui->setupUi(this);
}

HarvestRecordsinsert::~HarvestRecordsinsert()
{
    delete ui;
}

void HarvestRecordsinsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO harvestrecords (HarvestID, CropID, HarvestTime, HarvestedQuantity, Picker) VALUES (:HarvestID, :CropID, :HarvestTime, :HarvestedQuantity, :Picker); ");
        query.prepare(sql);
        query.bindValue(":HarvestID",ui->lineEdit->text());
        query.bindValue(":CropID", ui->lineEdit_2->text());
        query.bindValue(":HarvestTime", ui->lineEdit_3->text());
        query.bindValue(":HarvestedQuantity", ui->lineEdit_4->text());
        query.bindValue(":Picker", ui->lineEdit_5->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }

}

