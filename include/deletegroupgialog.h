#ifndef DELETEGROUPGIALOG_H
#define DELETEGROUPGIALOG_H

#include <QDialog>

namespace Ui {
class deletegroupgialog;
}

class deletegroupgialog : public QDialog
{
    Q_OBJECT

public:
    explicit deletegroupgialog(QWidget *parent = nullptr);
    ~deletegroupgialog();
    void setLabel(const QString txt) const;

private:
    Ui::deletegroupgialog *ui;
};

#endif // DELETEGROUPGIALOG_H
