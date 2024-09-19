#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
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
private:
    bool verifyEmail();
private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
