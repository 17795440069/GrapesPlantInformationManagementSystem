#ifndef GRAPESALESINSERT_H
#define GRAPESALESINSERT_H

#include <QWidget>

namespace Ui {
class GrapeSalesinsert;
}

class GrapeSalesinsert : public QWidget
{
    Q_OBJECT

public:
    explicit GrapeSalesinsert(QWidget *parent = nullptr);
    ~GrapeSalesinsert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GrapeSalesinsert *ui;
};

#endif // GRAPESALESINSERT_H
