#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"

#include <QRegularExpression>
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->get_verifycode_pushButton,&QPushButton::clicked,this,&RegisterDialog::getCode);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

bool RegisterDialog::verifyEmail(){
    auto email = ui->email_lineEdit->text();
    static const QRegularExpression regex(R"(^\w+(-+.\w+)*@\w+(-.\w+)*.\w+(-.\w+)*$)");
    bool match = regex.match(email).hasMatch();
    if(match){
        ui->error_label->setText("邮箱正确");
        ui->error_label->setStyleSheet("color: green;");
        return true;
    }else{
        ui->error_label->setText("邮箱不正确");
        ui->error_label->setStyleSheet("color: red;");
    }
    return false;
}

void RegisterDialog::getCode()
{
    if(verifyEmail()){
        // 发生 HTTP 请求
    }
}

