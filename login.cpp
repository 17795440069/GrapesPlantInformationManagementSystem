#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ini_file.h"
#include "informationwight.h"
#include "configwight.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/back2.jpg").scaled(this->size())));
    setPalette(pal);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(766,396); // 禁止改变窗口大小

    //设置无边框
    //setWindowFlag(Qt::FramelessWindowHint);

    //设置窗口标题
    this->setWindowTitle("登录");

    //设置密文登录
    ui->Edit_password->setEchoMode(QLineEdit::Password);

    if(ini_file().GetUsernameMemory()){
        ui->usernameMemoryCk->setChecked(true);
        ui->Edit_username->setText(ini_file().GetUsername());
    }else{
        ui->usernameMemoryCk->setChecked(false);
    }

    if(ini_file().GetPasswordMemory()){
        ui->passwordMemoryCk->setChecked(true);
        ui->Edit_password->setText(ini_file().GetPassword());
    }else{
        ui->passwordMemoryCk->setChecked(false);
    }
}

login::~login()
{
    delete ui;
}

void login::on_Button_login_clicked()
{

    if(ui->Edit_username->text()=="admin" && ui->Edit_password->text()=="123456"){
        this->close();
        bool first = ini_file().getFirst();
//        if(first){
//            configWight *t = new configWight();
//            t->show();
//        }else{
//            InformationWight *i = new InformationWight();
//            i->show();
//        }
        MainWindow *i = new MainWindow();
        i->show();
    }

    bool state = ui->usernameMemoryCk->checkState();
    if(state){
        QString username = ui->Edit_username->text();
        ini_file().SetUsernameMemory("1");
        ini_file().SetUsername(username);
    }else{
        QString username = "";
        ini_file().SetUsernameMemory("0");
        ini_file().SetUsername(username);
    }

    state = ui->passwordMemoryCk->checkState();
    if(state){
        QString password = ui->Edit_password->text();
        ini_file().SetPasswordMemory("1");
        ini_file().SetPassword(password);
    }else{
        QString password = "";
        ini_file().SetPasswordMemory("0");
        ini_file().SetPassword(password);
    }
}
