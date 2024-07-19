#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "product.h"
#include "sparePartGroup.h"
#include "warehouse.h"
#include "addgroupdialog.h"
#include "deletegroupgialog.h"
#include "addpartdialog.h"
#include "addpartstodialog.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Ui::MainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /*
     * Установка стартовых настроек и выполнение стартовых действий
     */
    void startSettings();
    /*
     * заполнить объекты тестовыми данными
     */
    void createObjects();
    /*
     * загрузка данных для СИСТЕМЫ ОБЕСПЕЧЕНИЯ
     */
    void loadSupportObjects();
    /*
     * загрузка данных для ИЗДЕЛИЯ
     */
    void loadProductObjects();
    /*
     * загрузка данных для СКЛАДОВ
     */
    void loadWarehouseObjects();
    void writeToXml();

private slots:
    /*
     * Обработчик нажатия кнопок слева (переключения вкладок)
     */
    void onTBTabsClicked();
    void onGroupTBClicked(QTableWidgetItem* item);
    void onAddGroupPbClicked();
    void onEditGroupPbClicked();
    void onDeleteGroupPbClicked();
    void onCreatePartPbClicked();
    void onEditPartPbClicked();
    void onDeletePartPbClicked();
    void onProductCbSelectionChanged();
    void onsparePartsTableSelectionChanged();

private:
    Ui::MainWindow *ui;
    QList<Product> products;
    QList<SparePartGroup> SparePartGroups;
    QList<Warehouse> warehouses;
    QList<SparePart> *spareParts;
    AddGroupDialog*     m_AddGroup_dialog;      ///< Виджет окна подключения к добавки групи, изделия или склада
    deletegroupgialog*  m_DeleteGroup_dialog;   ///< Виджет окна удаления групи, изделия или склада
    addpartDialog* m_CreatePart_dialog;         ///< Виджет окна подключения к добавки ЗЧ к группе
    addpartsToDialog* m_CreateParts_To_dialog;   ///< Виджет окна подключения к добавки ЗЧ к изделию или складу
};
#endif // MAINWINDOW_H
