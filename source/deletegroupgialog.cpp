#include "deletegroupgialog.h"
#include "ui_deletegroupgialog.h"

deletegroupgialog::deletegroupgialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletegroupgialog)
{
    ui->setupUi(this);
}

deletegroupgialog::~deletegroupgialog()
{
    delete ui;
}
void deletegroupgialog::setLabel(const QString txt) const{

    ui->label->setText(txt);
}
