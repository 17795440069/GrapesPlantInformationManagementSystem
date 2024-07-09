#ifndef PLANTINFORMATIONWIGHT_H
#define PLANTINFORMATIONWIGHT_H

#include <QWidget>
#include <QVariant>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
namespace Ui {
class plantinformationwight;
}

class plantinformationwight : public QWidget
{
    Q_OBJECT

public:
    explicit plantinformationwight(QWidget *parent = nullptr);
    ~plantinformationwight();


private slots:
    void select_sql(QStringList header,QString tableName);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();







    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_pushButton_10_clicked();

private:
    Ui::plantinformationwight *ui;

    QStringList header;
    QStringList table_name;


};

#endif // PLANTINFORMATIONWIGHT_H
