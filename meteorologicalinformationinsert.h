#ifndef METEOROLOGICALINFORMATIONINSERT_H
#define METEOROLOGICALINFORMATIONINSERT_H

#include <QWidget>

namespace Ui {
class MeteorologicalInformationinsert;
}

class MeteorologicalInformationinsert : public QWidget
{
    Q_OBJECT

public:
    explicit MeteorologicalInformationinsert(QWidget *parent = nullptr);
    ~MeteorologicalInformationinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MeteorologicalInformationinsert *ui;
};

#endif // METEOROLOGICALINFORMATIONINSERT_H
