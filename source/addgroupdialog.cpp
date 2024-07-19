#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::onGroupSavePbClicked()
{
    if( selection == 1 )        
    {
        if(editmode){
            m_group->setName(ui->name_le->text());
        }
        else
        {
            m_group = new SparePartGroup(ui->name_le->text());
        }
        accept();
    }
    else if( selection == 2 )
    {
        if(editmode){
            m_product->setName(ui->name_le->text());
        }
        else
        {
        m_product = new Product(ui->name_le->text());
        }
        accept();
    }
    else if( selection == 3 )
    {

        if(editmode){
            m_warehouse->setName(ui->name_le->text());
        }
        else
        {
        m_warehouse = new Warehouse(ui->name_le->text());
        }
        accept();
    }
}

void AddGroupDialog::setEditMode(bool n){
    editmode = n;
}


void AddGroupDialog::setSparePartGroup(const SparePartGroup &group) {
    ui->name_le->setText(group.getName());

}

void AddGroupDialog::setEditSparePartGroup(SparePartGroup *group) {
    m_group = group;
    ui->name_le->setText(group->getName());
}

void AddGroupDialog::setEditProduct(Product *product) {
    m_product = product;
    ui->name_le->setText(product->getName());
}

void AddGroupDialog::setEditWarehouse(Warehouse *warehouse){
    m_warehouse = warehouse;
    ui->name_le->setText(warehouse->getName());
}

Product AddGroupDialog::getProduct() const {
    return *m_product;
}

SparePartGroup AddGroupDialog::getSparePartGroup() const {
    return *m_group;
}

Warehouse AddGroupDialog::getWarehouse() const{
    return *m_warehouse;
}

void AddGroupDialog::setSelection( int s)
{
    selection = s;
}
