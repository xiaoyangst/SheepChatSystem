#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmanager.h"

#include <QRegularExpression>
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->get_verifycode_pushButton,&QPushButton::clicked,this,&RegisterDialog::getCode);
    connect(HttpManager::getInstance().get(),&HttpManager::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);
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

void RegisterDialog::initHttpHandlers()
{
    handlers_.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ui->error_label->setText("参数错误");
            ui->error_label->setStyleSheet("color: red;");
            return;
        }
        auto email = jsonObj["email"].toString();
        ui->error_label->setText("验证码已发送到邮箱");
        ui->error_label->setStyleSheet("color: green;");
        qDebug()<< "email is " << email ;
    });
}

void RegisterDialog::getCode()
{
    if(verifyEmail()){
        // 发生 HTTP 请求
    }
}

// 处理服务器的 response
void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{

    if(err != ErrorCodes::SUCCESS){
        ui->error_label->setText(tr("注册失败"));
        ui->error_label->setStyleSheet("color: red;");
        return;
    }

    // 解析 JSON
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8(),&jsonError);
    if(jsonError.error != QJsonParseError::NoError){
        ui->error_label->setText(tr("JSON 解析错误"));
        ui->error_label->setStyleSheet("color: red;");
        return;
    }

    if(!jsonDoc.isObject()){
        ui->error_label->setText(tr("JSON 解析错误"));
        ui->error_label->setStyleSheet("color: red;");
    }

    // 已确保可以正常解析 JSON 数据
    QJsonObject json_data = jsonDoc.object();
    handlers_[id](json_data);
    return;
}

