#include "addpartdialog.h"
#include "ui_addpartdialog.h"


addpartDialog::addpartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addpartDialog)
{
    ui->setupUi(this);
}

addpartDialog::~addpartDialog()
{
    delete ui;
}

void addpartDialog::setSparePartGroup(SparePartGroup *g){
    m_sparePartGroup = g;
}

void addpartDialog::onSavePartClicked(){

    QVector<double> dim(3);
    dim[0] = ui->le_length->text().toDouble();
    dim[1] = ui->le_width->text().toDouble();
    dim[2] = ui->le_hight->text().toDouble();

    m_sparePart = new SparePart(ui->le_name->text(), ui->le_price->text().toDouble(),
                                ui->le_mass->text().toDouble(), dim, m_sparePartGroup);
    accept();
}

SparePart addpartDialog::getSparePart(){
    return *m_sparePart;
}
