#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "identifier.h"
#include "sparePart.h"
#include "product.h"
#include "warehouse.h"
#include "supplySystem.h"
#include <QString>
#include <QDate>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // m_support_widget = new SupportWidget( this );
   // m_part_widget = new PartWidget( this );
    startSettings();
    createObjects();
    loadSupportObjects();
    writeToXml();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSettings() {

    ui->pb_add_group->hide();
    ui->pb_edit_group->hide();
    ui->pb_delete_group->hide();
    ui->pb_add_part->hide();
    ui->pb_edit_part->hide();
    ui->pb_delete_part->hide();
    ui->table_groups->setColumnCount(2);
    ui->table_groups->hideColumn(0);
    ui->table_supply_warehouses->setColumnCount(3);
    ui->table_supply_warehouses->setHorizontalHeaderLabels({"СКЛАД","Количество","Дата поставки"});
    ui->table_supply_warehouses->setColumnWidth(0,243);
    ui->table_spare_parts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_groups->setSelectionBehavior(QAbstractItemView::SelectRows);
    //stacked_widget->addWidget( m_support_widget );
}

void MainWindow::createObjects() {

    QVector<double> dimensions1 = {0.4, 0.4, 0.5};
    QVector<double> dimensions2 = {0.3, 0.3, 0.4};
    QVector<double> dimensions3 = {0.4, 0.4, 0.3};

    SparePartGroup _testGroup1("Двигатель");
    SparePartGroup _testGroup2("Трансмиссия");

    SparePart _testPart1("РПМ В СБОРЕ 2123", 13000, 12.0,dimensions1, _testGroup1);
    SparePart _testPart2("РЗМ В СБОРЕ 2121", 9000, 10.0,dimensions2, _testGroup2);
    SparePart _testPart3("РПМ В СБОРЕ 2121", 10200, 11.5,dimensions3, _testGroup2);

    Product _testProduct1("ВАЗ 2123");
    Product _testProduct2("ВАЗ 2121");

    Warehouse _testWarehouse1("Лебедушка");
    Warehouse _testWarehouse2("Тверь");

    SparePartGroups.append(_testGroup1);
    SparePartGroups.append(_testGroup2);

    QDate _partDate = QDate::currentDate();
    SparePartRecord _partRecord1(_testPart1,32, _partDate);
    SparePartRecord _partRecord2(_testPart2,8, _partDate);
    SparePartRecord _partRecord3(_testPart3,4, _partDate);
    _testWarehouse2.addPart(_partRecord1);
    _testWarehouse2.addPart(_partRecord2);
    _testWarehouse1.addPart(_partRecord3);
    _testProduct1.addPart(_partRecord1);
    _testProduct2.addPart(_partRecord2);
    _testProduct2.addPart(_partRecord3);

    products.append(_testProduct1);
    products.append(_testProduct2);

    warehouses.append(_testWarehouse1);
    warehouses.append(_testWarehouse2);

    spareParts = new QList<SparePart>();

    spareParts->append(_testPart1);
    spareParts->append(_testPart2);
    spareParts->append(_testPart3);

}

void MainWindow::loadSupportObjects(){

    ui->table_groups->clearContents();
    ui->table_groups->setRowCount(0);
    //ui->table_groups->setRowCount(SparePartGroups.count());
    ui->table_spare_parts->setColumnCount(5);
    ui->table_spare_parts->setHorizontalHeaderLabels({"№","Наименование","Стоимость,руб","Масса","Габариты, м"});
    ui->table_spare_parts->clearContents();
    ui->cb_product->clear();

    foreach (Product p, products) {

        ui->cb_product->addItem(p.getName(), p.getIdentifier());
    }
    int row = 0;
    foreach (SparePartGroup g, SparePartGroups){

        ui->table_groups->insertRow(row);
        QTableWidgetItem* id_item = new QTableWidgetItem();
        id_item->setText(g.getIdentifier());
        ui->table_groups->setItem(row,0,id_item);

        QTableWidgetItem* name_item = new QTableWidgetItem();
        name_item->setText(g.getName());
        ui->table_groups->setItem(row,1,name_item);
        if(row == 0){
            ui->table_groups->setItemSelected(name_item, true);
            ui->table_groups->setCurrentItem(name_item);
            onGroupTBClicked(id_item);
        }
        row++;
    }
    ui->table_groups->setColumnWidth(1,200);
    ui->table_spare_parts->selectRow(0);

}

void MainWindow::loadProductObjects(){

    ui->table_groups->clearContents();
    ui->table_groups->setRowCount(0);
    ui->table_spare_parts->setColumnCount(3);
    ui->table_spare_parts->setHorizontalHeaderLabels({"№","Наименование","Количество, шт."});
    ui->table_spare_parts->clearContents();

    int row=0;
    foreach(Product p, products){

        ui->table_groups->insertRow(row);
        QTableWidgetItem* id_item = new QTableWidgetItem();
        id_item->setText(p.getIdentifier());
        ui->table_groups->setItem(row,0,id_item);

        QTableWidgetItem* name_item = new QTableWidgetItem();
        name_item->setText(p.getName());
        ui->table_groups->setItem(row,1,name_item);
        if(row == 0){
            ui->table_groups->setItemSelected(name_item, true);
            ui->table_groups->setCurrentItem(name_item);
            onGroupTBClicked(id_item);
        }
        row=+1;
    }
    ui->table_spare_parts->selectRow(0);
}

void MainWindow::loadWarehouseObjects(){

    ui->table_groups->clearContents();
    ui->table_groups->setRowCount(0);
    ui->table_spare_parts->setColumnCount(4);
    ui->table_spare_parts->setHorizontalHeaderLabels({"№","Наименование","Количество, шт.","Дата поставки"});
    ui->table_spare_parts->clearContents();

    int row=0;
    foreach(Warehouse w, warehouses){

        ui->table_groups->insertRow(row);
        QTableWidgetItem* id_item = new QTableWidgetItem();
        id_item->setText(w.getIdentifier());
        ui->table_groups->setItem(row,0,id_item);

        QTableWidgetItem* name_item = new QTableWidgetItem();
        name_item->setText(w.getName());
        ui->table_groups->setItem(row,1,name_item);
        if(row == 0){
            ui->table_groups->setItemSelected(name_item, true);
            ui->table_groups->setCurrentItem(name_item);
            onGroupTBClicked(id_item);
        }
        row=+1;
    }
    ui->table_spare_parts->selectRow(0);
}

void MainWindow::onTBTabsClicked() {

    QToolButton* _tmpBtn = qobject_cast< QToolButton* >( QObject::sender() );
    QString _tmpBtn_txt = _tmpBtn->text();

    if( _tmpBtn_txt == "СИСТЕМА \n ОБЕСПЕЧЕНИЯ" ) {
        ui->cb_product->setVisible(true);
        ui->lb_product->setVisible(true);
        ui->pb_add_group->hide();
        ui->pb_edit_group->hide();
        ui->pb_delete_group->hide();
        ui->pb_add_part->hide();
        ui->pb_edit_part->hide();
        ui->pb_delete_part->hide();
        ui->lb_supply_warehouses->setVisible(true);
        ui->table_supply_warehouses->setVisible(true);

        ui->l_group->setText("ГРУППЫ ЗАПАСНЫХ ЧАСТЕЙ");
        ui->tb_support->setChecked(true);
        ui->tb_product->setChecked(false);
        ui->tb_spareParts->setChecked(false);
        ui->tb_warehouse->setChecked(false);

        loadSupportObjects();
        //stacked_widget->setCurrentWidget( m_support_widget );
    }
    else if ( _tmpBtn_txt == "ЗАПАСНЫЕ \n ЧАСТИ" ){
        ui->cb_product->hide();
        ui->lb_product->hide();
        ui->pb_add_group->setVisible(true);
        ui->pb_edit_group->setVisible(true);
        ui->pb_delete_group->setVisible(true);
        ui->pb_add_part->setVisible(true);
        ui->pb_edit_part->setVisible(true);
        ui->pb_delete_part->setVisible(true);
        ui->lb_supply_warehouses->hide();
        ui->table_supply_warehouses->hide();

        ui->l_group->setText("ГРУППЫ ЗАПАСНЫХ ЧАСТЕЙ");
        ui->tb_support->setChecked(false);;
        ui->tb_product->setChecked(false);
        ui->tb_spareParts->setChecked(true);
        ui->tb_warehouse->setChecked(false);

        loadSupportObjects();
    }
     else if ( _tmpBtn_txt == "ИЗДЕЛИЯ" ){
        ui->cb_product->hide();
        ui->lb_product->hide();
        ui->pb_add_group->setVisible(true);
        ui->pb_edit_group->setVisible(true);
        ui->pb_delete_group->setVisible(true);
        ui->pb_add_part->setVisible(true);
        ui->pb_edit_part->setVisible(true);
        ui->pb_delete_part->setVisible(true);
        ui->lb_supply_warehouses->hide();
        ui->table_supply_warehouses->hide();

        ui->l_group->setText("ИЗДЕЛИЯ");
        ui->tb_support->setChecked(false);
        ui->tb_product->setChecked(true);
        ui->tb_spareParts->setChecked(false);
        ui->tb_warehouse->setChecked(false);

        loadProductObjects();
    }
     else if ( _tmpBtn_txt == "СКЛАДЫ" ){
        ui->cb_product->hide();
        ui->lb_product->hide();
        ui->pb_add_group->setVisible(true);
        ui->pb_edit_group->setVisible(true);
        ui->pb_delete_group->setVisible(true);
        ui->pb_add_part->setVisible(true);
        ui->pb_edit_part->setVisible(true);
        ui->pb_delete_part->setVisible(true);
        ui->lb_supply_warehouses->hide();
        ui->table_supply_warehouses->hide();

        ui->l_group->setText("СКЛАДЫ");
        ui->tb_support->setChecked(false);
        ui->tb_product->setChecked(false);
        ui->tb_spareParts->setChecked(false);
        ui->tb_warehouse->setChecked(true);

        loadWarehouseObjects();
    }
}
void MainWindow::onGroupTBClicked(QTableWidgetItem* item){

    ui->table_spare_parts->clearContents();
       ui->table_spare_parts->setRowCount(0);
       int i = item->row(); // Получаем индекс строки
       QString _itemId = ui->table_groups->item(i, 0)->text();
       int row = 0;

       if (ui->tb_spareParts->isChecked() || ui->tb_support->isChecked()) {
           foreach (SparePart sp, *spareParts) {
               if (sp.getGroup().getIdentifier() == _itemId) {
                   ui->table_spare_parts->insertRow(row);

                   QTableWidgetItem* spare_id = new QTableWidgetItem();
                   spare_id->setText(sp.getIdentifier());
                   ui->table_spare_parts->setItem(row, 0, spare_id);

                   QTableWidgetItem* spare_name = new QTableWidgetItem();
                   spare_name->setText(sp.getName());
                   ui->table_spare_parts->setItem(row, 1, spare_name);

                   QTableWidgetItem* spare_price = new QTableWidgetItem();
                   spare_price->setText(QString::number(sp.getPrice()));
                   ui->table_spare_parts->setItem(row, 2, spare_price);

                   QTableWidgetItem* spare_mass = new QTableWidgetItem();
                   spare_mass->setText(QString::number(sp.getMass()));
                   ui->table_spare_parts->setItem(row, 3, spare_mass);

                   QTableWidgetItem* spare_dim = new QTableWidgetItem();
                   spare_dim->setText(sp.getFormatedDimensions());
                   ui->table_spare_parts->setItem(row, 4, spare_dim);

                   row += 1;
               }
           }

    }
    else if(ui->tb_product->isChecked()){
        foreach(Product p, products){
            if (p.getIdentifier() == _itemId){

                for( const auto& part : p.getSparePartRecord()){

                    ui->table_spare_parts->insertRow(row);

                    QTableWidgetItem* product_part_id = new QTableWidgetItem();
                    product_part_id->setText(part.sparePart.getIdentifier());
                    ui->table_spare_parts->setItem(row,0,product_part_id);

                    QTableWidgetItem* product_part_name = new QTableWidgetItem();
                    product_part_name->setText(part.sparePart.getName());
                    ui->table_spare_parts->setItem(row,1,product_part_name);

                    QTableWidgetItem* product_part_qty = new QTableWidgetItem();
                    product_part_qty->setText(QString::number(part.qty));
                    ui->table_spare_parts->setItem(row,2,product_part_qty);
                }
            }
        }
    }
    else if(ui->tb_warehouse->isChecked()){
        foreach(Warehouse wh, warehouses){
            if( wh.getIdentifier() == _itemId ){

                for (const auto& part : wh.getSparePartRecord()){

                    ui->table_spare_parts->insertRow(row);

                    QTableWidgetItem* warehouse_part_id = new QTableWidgetItem();
                    warehouse_part_id->setText(part.sparePart.getIdentifier());
                    ui->table_spare_parts->setItem(row,0,warehouse_part_id);

                    QTableWidgetItem* warehouse_part_name = new QTableWidgetItem();
                    warehouse_part_name->setText(part.sparePart.getName());
                    ui->table_spare_parts->setItem(row,1,warehouse_part_name);

                    QTableWidgetItem* warehouse_part_qty = new QTableWidgetItem();
                    warehouse_part_qty->setText(QString::number(part.qty));
                    ui->table_spare_parts->setItem(row,2,warehouse_part_qty);

                    QTableWidgetItem* warehouse_part_date = new QTableWidgetItem();
                    warehouse_part_date->setText((part.deliveryDate).toString("dd.MM.yyyy"));
                    ui->table_spare_parts->setItem(row,3,warehouse_part_date);

                }
            }
        }
    }
    ui->table_spare_parts->resizeColumnsToContents();
    ui->table_spare_parts->selectRow(0);
}
void MainWindow::onAddGroupPbClicked(){

    m_AddGroup_dialog = new AddGroupDialog(this);
    m_AddGroup_dialog->setEditMode(false);

    if(ui->tb_spareParts->isChecked()){

        m_AddGroup_dialog->setWindowTitle("ДОБАВИТЬ ГРУППУ ЗАПАСНЫХ ЧАСТЕЙ");
        m_AddGroup_dialog->show();
        m_AddGroup_dialog->setSelection(1);
        if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                SparePartGroup group = m_AddGroup_dialog->getSparePartGroup();
                SparePartGroups.append(group);
                loadSupportObjects();
            }

    }
    else if(ui->tb_product->isChecked()){

        m_AddGroup_dialog->setWindowTitle("ДОБАВИТЬ ИЗДЕЛИЕ");
        m_AddGroup_dialog->show();
        m_AddGroup_dialog->setSelection(2);
        if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                Product product = m_AddGroup_dialog->getProduct();
                products.append(product);
                loadProductObjects();
            }
    }
    else if(ui->tb_warehouse->isChecked()){

        m_AddGroup_dialog->setWindowTitle("ДОБАВИТЬ СКЛАД");
        m_AddGroup_dialog->show();
        m_AddGroup_dialog->setSelection(3);
        if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                Warehouse warehouse = m_AddGroup_dialog->getWarehouse();
                warehouses.append(warehouse);
                loadWarehouseObjects();
            }
    }
}
void MainWindow::onDeleteGroupPbClicked(){

    m_DeleteGroup_dialog = new deletegroupgialog(this);
    int _selectedRow = ui->table_groups->currentRow();
    if (_selectedRow < 0) return;

    QString _id = ui->table_groups->item(_selectedRow, 0)->text();
    QString _name = ui->table_groups->item(_selectedRow, 1)->text();

    m_DeleteGroup_dialog->setLabel("Вы действительно хотите удалить " + _name );

    if(ui->tb_spareParts->isChecked()){
        m_DeleteGroup_dialog->setWindowTitle("УДАЛИТЬ ГРУППУ ЗАПАСНЫХ ЧАСТЕЙ");
        m_DeleteGroup_dialog->show();
        if (m_DeleteGroup_dialog->exec() == QDialog::Accepted) {
            for( int i =0 ; i< SparePartGroups.size(); ++i){
                if(SparePartGroups[i].getIdentifier() == _id){
                    SparePartGroups.removeAt(i);
                    break;
                }
            }
            loadSupportObjects();
        }
    }
     else if(ui->tb_product->isChecked()){
        m_DeleteGroup_dialog->setWindowTitle("УДАЛИТЬ ИЗДЕЛИЕ");
        m_DeleteGroup_dialog->show();
        if (m_DeleteGroup_dialog->exec() == QDialog::Accepted) {
            for( int i =0 ; i< products.size(); ++i){
                if(products[i].getIdentifier() == _id){
                    products.removeAt(i);
                    break;
                }
            }
            loadProductObjects();
        }
    }
    else if(ui->tb_warehouse->isChecked()){
        m_DeleteGroup_dialog->setWindowTitle("УДАЛИТЬ СКЛАД");
        m_DeleteGroup_dialog->show();
        if (m_DeleteGroup_dialog->exec() == QDialog::Accepted) {
            for( int i =0 ; i< warehouses.size(); ++i){
                if(warehouses[i].getIdentifier() == _id){
                    warehouses.removeAt(i);
                    break;
                }
            }
            loadWarehouseObjects();
        }
    }
}

void MainWindow::onCreatePartPbClicked(){

    int _selectedRow = ui->table_groups->currentRow();
    QString _id = ui->table_groups->item(_selectedRow, 0)->text();
    QString _name = ui->table_groups->item(_selectedRow, 1)->text();


    if(ui->tb_spareParts->isChecked()){
        m_CreatePart_dialog = new addpartDialog(this);
        m_CreatePart_dialog->setWindowTitle("ДОБАВИТЬ ЗАПАСНУЮ ЧАСТЬ В ГРУППУ");
        m_CreatePart_dialog->show();
        SparePartGroup *group = new SparePartGroup();
        foreach(SparePartGroup g, SparePartGroups){
            if(g.getIdentifier() == _id){
                *group = g;
                break;
            }
        }
        m_CreatePart_dialog->setSparePartGroup(group);
        if(m_CreatePart_dialog->exec() == QDialog::Accepted){
            spareParts->append(m_CreatePart_dialog->getSparePart());
        }
        loadSupportObjects();
    }
    else if(ui->tb_product->isChecked()){
        m_CreateParts_To_dialog = new addpartsToDialog(this);
        m_CreateParts_To_dialog->setWindowTitle("ДОБАВИТЬ ЗАПАСНЫЕ ЧАСТИ К ИЗДЕЛИЮ");
        m_CreateParts_To_dialog->productFormat();
        m_CreateParts_To_dialog->setSpareParts(spareParts);
        m_CreateParts_To_dialog->show();
        if(m_CreateParts_To_dialog->exec() == QDialog::Accepted){
            foreach(Product p, products){
                if(p.getIdentifier() == _id){
                    p.addPart(m_CreateParts_To_dialog->getSparePartRecord());
                    products.replace(_selectedRow ,p);
                    break;
                }
            }
        }
        loadProductObjects();
    }
    else if(ui->tb_warehouse->isChecked()){
        m_CreateParts_To_dialog = new addpartsToDialog(this);
        m_CreateParts_To_dialog->setWindowTitle("ДОБАВИТЬ ЗАПАСНЫЕ ЧАСТИ НА СКЛАД");
        m_CreateParts_To_dialog->warehouseFormat();
        m_CreateParts_To_dialog->setSpareParts(spareParts);
        m_CreateParts_To_dialog->show();
        if(m_CreateParts_To_dialog->exec() == QDialog::Accepted){
            foreach(Warehouse w, warehouses){
                if(w.getIdentifier() == _id){
                    w.addPart(m_CreateParts_To_dialog->getSparePartRecord());
                    warehouses.replace(_selectedRow ,w);
                    break;
                }
            }
        }
        loadWarehouseObjects();
    }
}

void MainWindow::onDeletePartPbClicked(){

    m_DeleteGroup_dialog = new deletegroupgialog();
    int _selectedRow = ui->table_spare_parts->currentRow();
    if (_selectedRow < 0) return;
    QString _name = ui->table_spare_parts->item(_selectedRow, 1)->text();
    m_DeleteGroup_dialog->setWindowTitle("Удалить ЗЧ");
    m_DeleteGroup_dialog->setLabel("Вы действительно хотите удалить " + _name);
    m_DeleteGroup_dialog->show();
        if(ui->tb_spareParts->isChecked())
        {


            spareParts->removeAt(_selectedRow);
            loadSupportObjects();

        }
    else if(ui->tb_product->isChecked()) {
            if(m_DeleteGroup_dialog->exec() == QDialog::Accepted){
            for (Product &p : products) {
                auto spareParts = p.getSparePartRecord();
                            for (auto it = spareParts.begin(); it != spareParts.end(); ++it) {
                                if (it->sparePart.getIdentifier() == ui->table_spare_parts->item(_selectedRow, 0)->text()) {
                                    spareParts.erase(it);
                                    break;
                    }
                }
                            p.setSparePartRecord(spareParts);
            }           
        }
            loadProductObjects();
     }
     else if(ui->tb_warehouse->isChecked()) {
            if(m_DeleteGroup_dialog->exec() == QDialog::Accepted){
            for (Warehouse &w : warehouses){
                auto spareParts = w.getSparePartRecord();
                            for (auto it = spareParts.begin(); it != spareParts.end(); ++it) {
                                if (it->sparePart.getIdentifier() == ui->table_spare_parts->item(_selectedRow, 0)->text()) {
                                    spareParts.erase(it);
                                    break;
                    }
                }
                            w.setSparePartRecord(spareParts);
            }
         }
           loadWarehouseObjects();
     }
}

void MainWindow::writeToXml(){


    QFile sparePartsFile("/home/alexader/Desktop/work ennnt/untitled/spareParts.xml");

    if (!sparePartsFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to open file for writing:" << sparePartsFile.errorString();
        }


    QXmlStreamWriter sparePartsWriter(&sparePartsFile);
    sparePartsWriter.setAutoFormatting(true);
    sparePartsWriter.writeStartDocument();
    foreach(SparePart sp, *spareParts)
    {
        sp.writeToXml(sparePartsWriter);
    }
    sparePartsWriter.writeEndDocument();

    sparePartsFile.close();



    QFile ProductFile("/home/alexader/Desktop/work ennnt/untitled/products.xml");

    if (!ProductFile.open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to open file for writing:" << ProductFile.errorString();
            }


    QXmlStreamWriter ProductWriter(&ProductFile);
    ProductWriter.setAutoFormatting(true);
    ProductWriter.writeStartDocument();
    foreach(Product p, products)
    {
        p.writeToXml(ProductWriter);
    }
    ProductWriter.writeEndDocument();

    ProductFile.close();

    QFile warehouseFile("/home/alexader/Desktop/work ennnt/untitled/warehouses.xml");

    if (!warehouseFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to open file for writing:" << warehouseFile.errorString();
        }


    QXmlStreamWriter warehouseWriter(&warehouseFile);
    warehouseWriter.setAutoFormatting(true);
    warehouseWriter.writeStartDocument();
    foreach(Warehouse w, warehouses)
    {
        w.writeToXml(warehouseWriter);
    }
    warehouseWriter.writeEndDocument();

    warehouseFile.close();

    QFile spareGroupsFile("/home/alexader/Desktop/work ennnt/untitled/spareGroups.xml");

    if (!spareGroupsFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to open file for writing:" << spareGroupsFile.errorString();
        }


    QXmlStreamWriter spareGroupsWriter(&spareGroupsFile);
    spareGroupsWriter.setAutoFormatting(true);
    spareGroupsWriter.writeStartDocument();
    foreach(SparePartGroup group, SparePartGroups)
    {
        group.writeToXml(spareGroupsWriter);
    }
    spareGroupsWriter.writeEndDocument();

    spareGroupsFile.close();

}

void MainWindow::onProductCbSelectionChanged(){
/*
     QString product_id = ui->cb_product->currentData().toString();
     int row=0;
     foreach(Product p, products){
         if(p.getIdentifier() == product_id){

         }
     }
*/
}

void MainWindow::onsparePartsTableSelectionChanged(){

    ui->table_supply_warehouses->clearContents();
    ui->table_supply_warehouses->setRowCount(0);
    int _selectedRow = ui->table_spare_parts->currentRow();
    QString _id = ui->table_spare_parts->item(_selectedRow, 0)->text();
    int row = 0;
    foreach(Warehouse w, warehouses){
        //QVector<SparePartRecord> spr;
        foreach(SparePartRecord sp, w.getSparePartRecord()){
            if(sp.sparePart.getIdentifier()== _id){

                ui->table_supply_warehouses->insertRow(row);

                QTableWidgetItem* warehouse_name = new QTableWidgetItem();
                warehouse_name->setText(w.getName());
                ui->table_supply_warehouses->setItem(row,0,warehouse_name);

                QTableWidgetItem* warehouse_qty = new QTableWidgetItem();
                warehouse_qty->setText(QString::number(sp.qty));
                ui->table_supply_warehouses->setItem(row,1,warehouse_qty);

                QTableWidgetItem* warehouse_date= new QTableWidgetItem();
                warehouse_date->setText(sp.deliveryDate.toString("dd/MM/yyyy"));
                ui->table_supply_warehouses->setItem(row,2,warehouse_date);

                row++;
            }
        }
    }
}

void MainWindow::onEditGroupPbClicked(){
    m_AddGroup_dialog = new AddGroupDialog(this);
    m_AddGroup_dialog->setEditMode(true);

    int _selectedRow = ui->table_groups->currentRow();
    if (_selectedRow < 0) return;

    QString _id = ui->table_groups->item(_selectedRow, 0)->text();


    if(ui->tb_spareParts->isChecked()){

        SparePartGroup *group = nullptr;

        for (int i = 0; i < SparePartGroups.size(); ++i) {
            if (SparePartGroups[i].getIdentifier() == _id) {
                group = &SparePartGroups[i];
                break;
            }
        }

        if (group) {
            m_AddGroup_dialog->setWindowTitle("РЕДАКТИРОВАТЬ ГРУППУ ЗАПАСНЫХ ЧАСТЕЙ");
            m_AddGroup_dialog->setEditSparePartGroup(group);
            m_AddGroup_dialog->show();
            m_AddGroup_dialog->setSelection(1);
            if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                loadSupportObjects();
                onGroupTBClicked(ui->table_groups->item(_selectedRow, 0));
            }
        }
    }
    else if(ui->tb_product->isChecked()){

        Product *product = nullptr;

        for (int i = 0; i < SparePartGroups.size(); ++i) {
            if (products[i].getIdentifier() == _id) {
                product = &products[i];
                break;
            }
        }

        if (product) {
            m_AddGroup_dialog->setWindowTitle("РЕДАКТИРОВАТЬ Изделия");
            m_AddGroup_dialog->setEditProduct(product);
            m_AddGroup_dialog->show();
            m_AddGroup_dialog->setSelection(2);
            if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                loadProductObjects();
                onGroupTBClicked(ui->table_groups->item(_selectedRow, 0));
            }
        }
    }
    else if(ui->tb_warehouse->isChecked()){

        Warehouse *warehouse= nullptr;

        for (int i = 0; i < SparePartGroups.size(); ++i) {
            if (warehouses[i].getIdentifier() == _id) {
                warehouse = &warehouses[i];
                break;
            }
        }

        if (warehouse) {
            m_AddGroup_dialog->setWindowTitle("РЕДАКТИРОВАТЬ Изделия");
            m_AddGroup_dialog->setEditWarehouse(warehouse);
            m_AddGroup_dialog->show();
            m_AddGroup_dialog->setSelection(3);
            if (m_AddGroup_dialog->exec() == QDialog::Accepted) {
                loadWarehouseObjects();
                onGroupTBClicked(ui->table_groups->item(_selectedRow, 0));
            }
        }
    }
}
void MainWindow::onEditPartPbClicked(){

}

