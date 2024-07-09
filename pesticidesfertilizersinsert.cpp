#include "pesticidesfertilizersinsert.h"
#include "ui_pesticidesfertilizersinsert.h"
#include "plantinformationwight.h"
#include <QMessageBox>
#include "sharevar.h"
PesticidesFertilizersinsert::PesticidesFertilizersinsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PesticidesFertilizersinsert)
{
    ui->setupUi(this);
}

PesticidesFertilizersinsert::~PesticidesFertilizersinsert()
{
    delete ui;
}

void PesticidesFertilizersinsert::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    if(function_sql==1){
        sql = QString("INSERT INTO pesticidesfertilizers (ProductID, ProductName, Ingredients, UsageAmount, UsageTime,BaseID) VALUES (:ProductID, :ProductName, :Ingredients, :UsageAmount, :UsageTime,:BaseID); ");
        query.prepare(sql);
        query.bindValue(":ProductID",ui->lineEdit->text());
        query.bindValue(":ProductName", ui->lineEdit_2->text());
        query.bindValue(":Ingredients", ui->lineEdit_3->text());
        query.bindValue(":UsageAmount", ui->lineEdit_4->text());
        query.bindValue(":UsageTime", ui->lineEdit_5->text());
        query.bindValue(":BaseID", ui->lineEdit_6->text());
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "插入信息失败：" + query.lastError().text());
        } else {
            close();
        }
    }

}

