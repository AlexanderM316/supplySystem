#ifndef ADDPARTDIALOG_H
#define ADDPARTDIALOG_H

#include <QDialog>
#include <QString>
#include "sparePart.h"
#include "sparePartGroup.h"

namespace Ui {
class addpartDialog;
}

class addpartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addpartDialog(QWidget *parent = nullptr);
    ~addpartDialog();
    void setSparePartGroup(SparePartGroup *g);
    SparePart getSparePart();

private slots:

    void onSavePartClicked();

private:
    Ui::addpartDialog *ui;
    SparePart *m_sparePart;
    SparePartGroup *m_sparePartGroup;

};

#endif // ADDPARTDIALOG_H
