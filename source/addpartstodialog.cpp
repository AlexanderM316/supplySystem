#include "addpartstodialog.h"
#include "ui_addpartstodialog.h"
#include <QDebug>
addpartsToDialog::addpartsToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addpartsToDialog)
{
    ui->setupUi(this);
}

void addpartsToDialog::setSpareParts(QList<SparePart> *sp){
    m_spareParts = sp;
    fillCbPartName();
}

void addpartsToDialog::fillCbPartName(){

    foreach (SparePart sp, *m_spareParts) {

        ui->cb_part_name->addItem(sp.getName());
    }
}

addpartsToDialog::~addpartsToDialog()
{
    delete ui;
}

void addpartsToDialog::productFormat(){
    ui->lb_delivery_date->hide();
    ui->de_delivery_date->hide();
}

void addpartsToDialog::warehouseFormat(){
    ui->lb_delivery_date->setVisible(true);
    ui->de_delivery_date->setVisible(true);
}

void addpartsToDialog::onSavePartClicked(){


    foreach(SparePart sp, *m_spareParts){
        if( sp.getName() == ui->cb_part_name->currentText()){
            //m_sparePart = &sp;

            // таким образом новое identifier будеть генерервоця
            m_sparePart = new SparePart(sp.getName(),sp.getPrice(),sp.getMass(),
                                        sp.getDimensions(),sp.getGroup());
        }
    }

    m_sparePartRecord = new SparePartRecord(m_sparePart,ui->le_qty->text().toInt(),
                                            QDate::fromString(ui->de_delivery_date->text(),"dd/MM/yyyy"));

    accept();

}

SparePartRecord  addpartsToDialog::getSparePartRecord(){
    return *m_sparePartRecord;
}
