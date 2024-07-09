#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSettings>
#include<QFileInfo>
#include "ini_file.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_Button_login_clicked();



private:
    Ui::login *ui;
};

#endif // LOGIN_H
