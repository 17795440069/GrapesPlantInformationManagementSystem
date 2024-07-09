#ifndef PESTICIDESFERTILIZERSINSERT_H
#define PESTICIDESFERTILIZERSINSERT_H

#include <QWidget>

namespace Ui {
class PesticidesFertilizersinsert;
}

class PesticidesFertilizersinsert : public QWidget
{
    Q_OBJECT

public:
    explicit PesticidesFertilizersinsert(QWidget *parent = nullptr);
    ~PesticidesFertilizersinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PesticidesFertilizersinsert *ui;
};

#endif // PESTICIDESFERTILIZERSINSERT_H
