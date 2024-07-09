#include "grapesalesinsert.h"
#include "ui_grapesalesinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
#include <QDebug>
QSqlQuery query;
QString sql;

GrapeSalesinsert::GrapeSalesinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrapeSalesinsert)
{
    ui->setupUi(this);

}

GrapeSalesinsert::~GrapeSalesinsert()
{
    delete ui;
}

void GrapeSalesinsert::on_pushButton_clicked()
{


    if(function_sql==1){
        sql = QString("INSERT INTO grapesalesinsert (SaleID, CropID, SalesChannel, SalesPrice, SalesVolume,SaleDate) VALUES (:SaleID, :CropID, :SalesChannel, :SalesPrice, :SalesVolume,:SaleDate); ");
        query.prepare(sql);
        query.bindValue(":SaleID",ui->lineEdit->text());
        query.bindValue(":CropID", ui->lineEdit_2->text());
        query.bindValue(":SalesChannel", ui->lineEdit_3->text());
        query.bindValue(":SalesPrice", ui->lineEdit_4->text());
        query.bindValue(":SalesVolume", ui->lineEdit_5->text());
        query.bindValue(":SaleDate", ui->lineEdit_6->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }
}

