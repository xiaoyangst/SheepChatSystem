#include "register_dialog.h"
#include "ui_register_dialog.h"

Register_Dialog::Register_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register_Dialog)
{
    ui->setupUi(this);
}

Register_Dialog::~Register_Dialog()
{
    delete ui;
}
