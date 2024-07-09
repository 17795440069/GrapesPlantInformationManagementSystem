#include "plantingcropsinsert.h"
#include "ui_plantingcropsinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
plantingcropsinsert::plantingcropsinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plantingcropsinsert)
{
    ui->setupUi(this);
}

plantingcropsinsert::~plantingcropsinsert()
{
    delete ui;
}

void plantingcropsinsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO plantingcrops (CropID, BaseID, CropType, Variety, PlantingArea,EstimatedYield) VALUES (:CropID, :BaseID, :CropType, :Variety, :PlantingArea,:EstimatedYield); ");
        query.prepare(sql);
        query.bindValue(":CropID",ui->lineEdit->text());
        query.bindValue(":BaseID", ui->lineEdit_2->text());
        query.bindValue(":CropType", ui->lineEdit_3->text());
        query.bindValue(":Variety", ui->lineEdit_4->text());
        query.bindValue(":PlantingArea", ui->lineEdit_5->text());
        query.bindValue(":EstimatedYield", ui->lineEdit_6->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }

}

