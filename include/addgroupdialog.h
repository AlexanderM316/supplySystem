#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include "product.h"
#include "sparePartGroup.h"
#include "warehouse.h"

namespace Ui {
class AddGroupDialog;
}

class AddGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGroupDialog(QWidget *parent = nullptr);
    ~AddGroupDialog();
    Product getProduct() const;
    SparePartGroup getSparePartGroup() const;
    Warehouse getWarehouse() const;
    void setSelection( int s);
    void setSparePartGroup(const SparePartGroup &group);
    void setEditSparePartGroup(SparePartGroup *group);
    void setEditProduct(Product *product);
    void setEditWarehouse(Warehouse *warehouse);
    void setEditMode(bool n);
private slots:

    void onGroupSavePbClicked();

private:
    Ui::AddGroupDialog *ui;
    Product *m_product;
    SparePartGroup *m_group;
    Warehouse *m_warehouse;
    int selection;  ///< 1 дла ДОБАВЛЕНИЯ ГРУППУ ЗАПАСНЫХ ЧАСТЕЙ,
                    ///< 2 дла ДОБАВЛЕНИЯ ИЗДЕЛИЕ,
                    ///< 3 дла ДОБАВЛЕНИЯ СКЛАДА
    bool editmode;  ///
};

#endif // ADDGROUPDIALOG_H
