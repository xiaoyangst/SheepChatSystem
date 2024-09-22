#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
/******************************************************************************
 *
 * @file       registerdialog.h
 * @brief      注册界面
 *
 * @author     xiaoyangst
 * @date       2024/09/18
 * @history
 *****************************************************************************/
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
private slots:
    void getCode();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    bool verifyEmail();
    void initHttpHandlers();
private:
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
};

#endif // REGISTERDIALOG_H
