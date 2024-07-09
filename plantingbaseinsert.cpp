#include "plantingbaseinsert.h"
#include "ui_plantingbaseinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
PlantingBaseInsert::PlantingBaseInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlantingBaseInsert)
{
    ui->setupUi(this);
}

PlantingBaseInsert::~PlantingBaseInsert()
{
    delete ui;
}

void PlantingBaseInsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO plantingbase (BaseID, BaseName, BaseAddress, BaseManager, ContactPhone) VALUES (:BaseID, :BaseName, :BaseAddress, :BaseManager, :ContactPhone); ");
        query.prepare(sql);
        query.bindValue(":BaseID",ui->lineEdit->text());
        query.bindValue(":BaseName", ui->lineEdit_2->text());
        query.bindValue(":BaseAddress", ui->lineEdit_3->text());
        query.bindValue(":BaseManager", ui->lineEdit_4->text());
        query.bindValue(":ContactPhone", ui->lineEdit_5->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }


}

