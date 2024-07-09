#ifndef HARVESTRECORDSINSERT_H
#define HARVESTRECORDSINSERT_H

#include <QWidget>

namespace Ui {
class HarvestRecordsinsert;
}

class HarvestRecordsinsert : public QWidget
{
    Q_OBJECT

public:
    explicit HarvestRecordsinsert(QWidget *parent = nullptr);
    ~HarvestRecordsinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HarvestRecordsinsert *ui;
};

#endif // HARVESTRECORDSINSERT_H
