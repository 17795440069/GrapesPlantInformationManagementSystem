#include "plantinformationwight.h"
#include "ui_plantinformationwight.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include "plantingbaseinsert.h"
#include "plantingcropsinsert.h"
#include "sharevar.h"
#include "grapesalesinsert.h"
#include "growthrecordsinsert.h"
#include "harvestrecordsinsert.h"
#include "meteorologicalinformationinsert.h"
#include "pesticidesfertilizersinsert.h"
#include <QTableWidgetItem>
QStringList table_name;
QStringList table_shuxing_1;
QStringList table_shuxing_2;
QStringList table_shuxing_3;
QStringList table_shuxing_4;
QStringList table_shuxing_5;
QStringList table_shuxing_6;
QStringList table_shuxing_7;
plantinformationwight::plantinformationwight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plantinformationwight)
{
    ui->setupUi(this);
    table_name<<"plantingbase"<<"plantingcrops"<<"pesticidesfertilizers"<<"growthrecords"<<"harvestrecords"<<"meteorologicalinformation"<<"grapesales";
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("bj-cynosdbmysql-grp-bartcsz8.sql.tencentcdb.com");
    db.setPort(27616);
    //db.setPort(3306);
    db.setDatabaseName("db_managementSystem"); //不是Database,记得别填错
    db.setUserName("root");
    db.setPassword("537719LxN.");

    bool ok = db.open();
    if (ok){
        ui->label->setText("数据库连接状态：正常");
        ui->label->setStyleSheet("color:green;");
    }
    else {
        QMessageBox::critical(0, QObject::tr("Databse Error"), db.lastError().text());
        ui->label->setText("数据库连接状态：失败！请检查相关配置。");
        ui->label->setStyleSheet("color:black;");
    }
    current_table = 1;
    on_pushButton_11_clicked();
    table_name<<"PlantingBase"<<"PlantingCrops"<<"PesticidesFertilizers"<<"GrowthRecords"<<"HarvestRecords"<<"MeteorologicalInformation"<<"GrapeSales";
    table_shuxing_1<<"BaseID"<<"BaseName"<<"BaseAddress"<<"BaseManager"<<"ContactPhone";
    table_shuxing_2<<"CropID"<<"BaseID"<<"CropType"<<"Variety"<<"PlantingArea"<<"EstimatedYield";
    table_shuxing_3<<"ProductID"<<"ProductName"<<"Ingredients"<<"UsageAmount"<<"UsageTime"<<"BaseID";
    table_shuxing_4<<"RecordID"<<"CropID"<<"BaseID"<<"GrowthPhase"<<"RecordDate";
    table_shuxing_5<<"HarvestID"<<"CropID"<<"HarvestTime"<<"HarvestedQuantity"<<"Picker";
    table_shuxing_6<<"InfoID"<<"RecordingTime"<<"Temperature"<<"Rainfall"<<"Humidity";
    table_shuxing_7<<"SaleID"<<"CropID"<<"SalesChannel"<<"SalesPrice"<<"SalesVolume"<<"SaleDate";
}

plantinformationwight::~plantinformationwight()
{
    db.close();
    delete ui;
}
void plantinformationwight::select_sql(QStringList header,QString tableName)
{
    qDebug()<<tableName<<"表的查询";
    QString sql = "";
    QSqlQuery query;
    int row =0;
    int columns = 0;

    //初始化行数
    sql = QString("SELECT count(*) FROM "+tableName);
    qDebug()<<sql;
//query.exec(sql);
    if (!query.exec(sql)) {
        //QMessageBox::critical(this, "错误", "查询信息失败：" + query.lastError().text());
        qDebug()<<query.lastError().text();
    }
    if(query.next())
    {
        row =  query.value(0).toInt();
        qDebug()<<"row: "<<QString(row);
        ui->tableWidget->setRowCount(row);
    }
    //初始化列数（mysql中存在一个information_schema这个数据库，存放各个表的信息）
    sql = QString("select * from "+tableName);
    qDebug()<<sql;
    query.exec(sql);
    if(query.next())
    {
        columns = query.record().count();
        qDebug()<<"columns: "<<QString(row);
        ui->tableWidget->setColumnCount(columns);//列
    }
    //2.设置表头
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //自动调整宽度
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //将数据库中的数据写入表格
    sql = QString("select * from "+tableName);
    qDebug()<<sql;
    query.exec(sql);
    for(int i = 0; query.next(); i++)
    {
        for(int j = 0; j < columns; j++)
        {
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(query.value(j).toString()));
        }
    }
}
void plantinformationwight::on_pushButton_clicked()
{
    current_table = 1;
    header.clear();
    header<<"基地ID"<<"基地名称"<<"基地地址"<<"负责人"<<"联系电话";
    select_sql(header,"plantingbase");
}


void plantinformationwight::on_pushButton_2_clicked()
{
    current_table = 2;
    //种植作物
    header.clear();
    header<<"作物ID"<<"基地ID"<<"作物类型"<<"品种"<<"种植面积"<<"预计产量";
    select_sql(header,"plantingcrops");
}


void plantinformationwight::on_pushButton_3_clicked()
{
    current_table = 3;
    //农药肥料
    header.clear();
    header<<"产品ID"<<"产品名称"<<"成分"<<"使用量"<<"使用时间"<<"基地ID";
    select_sql(header,"pesticidesfertilizers");
}


void plantinformationwight::on_pushButton_4_clicked()
{
    current_table = 4;
    //生长记录
    header.clear();
    header<<"记录ID"<<"作物ID"<<"生长周期"<<"记录日期";
    select_sql(header,"growthrecords");
}


void plantinformationwight::on_pushButton_7_clicked()
{
    current_table = 5;
    //采摘记录
    header.clear();
    header<<"采摘ID"<<"作物ID"<<"采摘时间"<<"采摘数量"<<"采摘人";
    select_sql(header,"harvestrecords");
}


void plantinformationwight::on_pushButton_8_clicked()
{
    current_table = 6;
    //气象信息
    //采摘记录
    header.clear();
    header<<"日志ID"<<"记录时间"<<"温度"<<"降雨量"<<"湿度";
    select_sql(header,"meteorologicalinformation");
}


void plantinformationwight::on_pushButton_5_clicked()
{
    current_table = 7;
    //葡萄销售
    header.clear();
    header<<"销售ID"<<"销售渠道"<<"销售价格"<<"销售量"<<"销售日期";
    select_sql(header,"grapesales");
}


void plantinformationwight::on_pushButton_11_clicked()
{
    switch (current_table) {
        case 1: on_pushButton_clicked();break;
        case 2: on_pushButton_2_clicked();break;
        case 3: on_pushButton_3_clicked();break;
        case 4: on_pushButton_4_clicked();break;
        case 5: on_pushButton_7_clicked();break;
        case 6: on_pushButton_8_clicked();break;
        case 7: on_pushButton_5_clicked();break;
        default: on_pushButton_clicked();
    }
}


void plantinformationwight::on_pushButton_6_clicked()
{
    function_sql = 1;
    qDebug()<<"种植基地插入窗口";
    if(current_table==1){
        PlantingBaseInsert *insert_wight = new PlantingBaseInsert();
        insert_wight->show();
    }else if(current_table==2){
        plantingcropsinsert *insert_wight = new plantingcropsinsert();
        insert_wight->show();
    }else if (current_table==3) {
        PesticidesFertilizersinsert *insert_wight = new PesticidesFertilizersinsert();
        insert_wight->show();
    }else if (current_table==4) {
        GrowthRecordsinsert *insert_wight = new GrowthRecordsinsert();
        insert_wight->show();
    }else if (current_table==5) {
        HarvestRecordsinsert *insert_wight = new HarvestRecordsinsert();
        insert_wight->show();
    }else if (current_table==6) {
        MeteorologicalInformationinsert *insert_wight = new MeteorologicalInformationinsert();
        insert_wight->show();
    }else if (current_table==7) {
        GrapeSalesinsert *insert_wight = new GrapeSalesinsert();
        insert_wight->show();
    }
}


void plantinformationwight::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(previousRow!=-1){
        if(previousColumn==0){
            return;
        }
        if (!db.open()) {
            qDebug() << "无法打开数据库";
            return;
        }
        QString shuxing;
        QString id;
        switch (current_table) {
            case 1:shuxing = table_shuxing_1.at(previousColumn); id =table_shuxing_1.at(0);break;
            case 2:shuxing = table_shuxing_2.at(previousColumn); id =table_shuxing_2.at(0);break;
            case 3:shuxing = table_shuxing_3.at(previousColumn); id =table_shuxing_3.at(0);break;
            case 4:shuxing = table_shuxing_4.at(previousColumn); id =table_shuxing_4.at(0);break;
            case 5:shuxing = table_shuxing_5.at(previousColumn); id =table_shuxing_5.at(0);break;
            case 6:shuxing = table_shuxing_6.at(previousColumn); id =table_shuxing_6.at(0);break;
            case 7:shuxing = table_shuxing_7.at(previousColumn); id =table_shuxing_7.at(0);break;
        }

        QString name = ui->tableWidget->item(previousRow,0)->text();
        QString tablename = table_name.at(current_table-1);
        QSqlQuery query;
        QString sql = QString("UPDATE %1 SET %2 = :value WHERE %3=%4").arg(tablename).arg(shuxing).arg(id).arg(name);
        query.prepare(sql);
        query.bindValue(":value", ui->tableWidget->item(previousRow,previousColumn)->text());
        qDebug() <<sql;
        if (!query.exec()) {
            qDebug() << "更新数据失败：" << query.lastError().text();
        } else {
            qDebug() << "更新数据成功";
        }

    }



}


void plantinformationwight::on_pushButton_10_clicked()
{
    QString shuxing;
    QString id;
    QString tablename = table_name.at(current_table-1);
    switch (current_table) {
        case 1:id =table_shuxing_1.at(0);break;
        case 2:id =table_shuxing_2.at(0);break;
        case 3:id =table_shuxing_3.at(0);break;
        case 4:id =table_shuxing_4.at(0);break;
        case 5:id =table_shuxing_5.at(0);break;
        case 6:id =table_shuxing_6.at(0);break;
        case 7:id =table_shuxing_7.at(0);break;
    }
    //DELETE FROM Websites WHERE name='Facebook' AND country='USA';
    QSqlQuery query;
    QString name = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    QString sql = QString("DELETE FROM %1 WHERE %2=%3;").arg(tablename).arg(id).arg(name);
    query.prepare(sql);
    //qDebug() <<sql;
    if (!query.exec()) {
        qDebug() << "删除数据失败：" << query.lastError().text();
    } else {
        qDebug() << "删除数据成功";
        on_pushButton_6_clicked();
    }
    //qDebug()<< ui->tableWidget->currentRow();
}

