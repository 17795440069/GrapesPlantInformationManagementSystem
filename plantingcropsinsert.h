#ifndef PLANTINGCROPSINSERT_H
#define PLANTINGCROPSINSERT_H

#include <QWidget>

namespace Ui {
class plantingcropsinsert;
}

class plantingcropsinsert : public QWidget
{
    Q_OBJECT

public:
    explicit plantingcropsinsert(QWidget *parent = nullptr);
    ~plantingcropsinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::plantingcropsinsert *ui;
};

#endif // PLANTINGCROPSINSERT_H
