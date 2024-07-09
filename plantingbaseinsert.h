#ifndef PLANTINGBASEINSERT_H
#define PLANTINGBASEINSERT_H

#include <QWidget>

namespace Ui {
class PlantingBaseInsert;
}

class PlantingBaseInsert : public QWidget
{
    Q_OBJECT

public:
    explicit PlantingBaseInsert(QWidget *parent = nullptr);
    ~PlantingBaseInsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PlantingBaseInsert *ui;
};

#endif // PLANTINGBASEINSERT_H
