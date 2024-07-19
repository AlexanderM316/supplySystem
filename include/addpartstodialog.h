#ifndef ADDPARTSTODIALOG_H
#define ADDPARTSTODIALOG_H

#include <QDialog>
#include "sparePartRecord.h"
#include "sparePart.h"

namespace Ui {
class addpartsToDialog;
}

class addpartsToDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addpartsToDialog(QWidget *parent = nullptr);
    ~addpartsToDialog();
    void productFormat();
    void warehouseFormat();
    void fillCbPartName();
    void setSpareParts(QList<SparePart> *sp);
    SparePartRecord getSparePartRecord();
    
private slots:

    void onSavePartClicked();

private:
    Ui::addpartsToDialog *ui;
    SparePartRecord *m_sparePartRecord;
    SparePart *m_sparePart;
    QList<SparePart> *m_spareParts;

};

#endif // ADDPARTSTODIALOG_H
