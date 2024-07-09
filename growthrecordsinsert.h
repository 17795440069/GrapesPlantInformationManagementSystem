#ifndef GROWTHRECORDSINSERT_H
#define GROWTHRECORDSINSERT_H

#include <QWidget>

namespace Ui {
class GrowthRecordsinsert;
}

class GrowthRecordsinsert : public QWidget
{
    Q_OBJECT

public:
    explicit GrowthRecordsinsert(QWidget *parent = nullptr);
    ~GrowthRecordsinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GrowthRecordsinsert *ui;
};

#endif // GROWTHRECORDSINSERT_H
