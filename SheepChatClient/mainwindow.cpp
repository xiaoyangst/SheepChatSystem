#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginUI_(new LoginDialog(this))
    , registerUI_(new RegisterDialog(this))
{
    ui->setupUi(this);
    setCentralWidget(loginUI_);
    loginUI_->show();

    connect(loginUI_,&LoginDialog::switchRegister,this,&MainWindow::openRegisterUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openRegisterUI(){
    setCentralWidget(registerUI_);
    loginUI_->hide();
    registerUI_->show();
}
