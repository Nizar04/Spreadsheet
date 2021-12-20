#ifndef GODIALOG_H
#define GODIALOG_H

#include <QDialog>
namespace Ui {
class GoDialog;
}

class GoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GoDialog(QWidget *parent = nullptr);~GoDialog() ;
    QString getCell() const                                  ;

private:
    Ui::GoDialog *ui;
};
#endif // GODIALOG_H
