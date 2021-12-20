#include "godialog.h"
#include "ui_godialog.h"
#include <QRegExp>
#include <QRegExpValidator>

GoDialog::GoDialog(QWidget *parent) :QDialog(parent),ui(new Ui::GoDialog)
{    ui  ->  setupUi(this);
     QRegExp exp{"[A-Z][1-9]{0,2}"};
     ui  ->  lineEdit->setValidator(new QRegExpValidator(exp));
}

GoDialog::~GoDialog()
{    delete ui;    }
QString GoDialog::getCell() const
{    return ui->lineEdit->text();   }
