#include "texteditor.h"
#include "ui_texteditor.h"

textEditor::textEditor(QWidget *parent): QMainWindow(parent), ui(new Ui::textEditor)
{
    ui  ->  setupUi(this)                          ;
    setCentralWidget(ui  ->  plainTextEdit)        ;
    connect(ui  ->  action_Save_As,&QAction::triggered,this, &textEditor::saveas)   ;
   // connect(ui  ->action_Save,&QAction::triggered,this, &textEditor::save)        ;
}
textEditor::~textEditor()
{  delete ui; }
void textEditor::act_new()
{
    currentFile.clear()                                ;
    currentFile=nullptr                                ;
    ui  ->  plainTextEdit  ->  setPlainText(QString())         ;
    ui  ->  statusbar  ->  showMessage("Creating file")  ;
}
void textEditor::act_open()
{
    QString filename= QFileDialog::getOpenFileName(this,"Open file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    QMessageBox::warning(this,"Sorry","Cannot open desired file :"+file.errorString());
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
    ui->statusbar->showMessage("Opening the chosen file...");
}
void textEditor::act_copy()
{    ui->plainTextEdit->copy();
     ui->statusbar->showMessage("Copying the current selection");
}
void textEditor::act_paste()
{   ui  ->  plainTextEdit  ->  paste();
    ui  ->  statusbar  ->  showMessage("Pasting the previous copied selection");
}
void textEditor::act_cut()
{    ui  ->  plainTextEdit  ->  cut();
     ui  ->  statusbar  ->  showMessage("Cutting the current selection");
}
void textEditor::act_exit()
{    ui  ->  statusbar  ->  showMessage("Quitting ...");
     QApplication::quit();
}
void textEditor::act_qt()
{    QMessageBox::aboutQt(this, "About Me");
     ui  ->  statusbar  ->  showMessage("About Qt...");
}
void textEditor::act_about()
{    QMessageBox::about(this, tr("About Application"),
             tr("The <b>Application</b> example demonstrates how to "
                "write modern GUI applications using Qt, with a menu bar, "
                "toolbars, and a status bar."));
    ui->statusbar->showMessage("About ...");
}


bool textEditor::save_file(const QString &filename)
{
    QString errorMessage                                ;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor)  ;
    QSaveFile file(filename)                            ;
    if (file.open(QFile::WriteOnly)) {
        QTextStream out(&file)                   ;
        out << ui->plainTextEdit->toPlainText()  ;
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(filename), file.errorString());
        }    } 
    else {
            errorMessage = tr("Cannot open file %1 for writing:\n%2.").arg(QDir::toNativeSeparators(filename), file.errorString());
    }
    QApplication::restoreOverrideCursor();
    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;    }
    set_file(filename)                                    ;
    statusBar()  ->  showMessage(tr("File saved"), 2000)  ;
    return true;
}
bool textEditor::save()
{    if (currentFile.isEmpty()) {
        return saveas();    }
     else {
        return save_file(currentFile);    }
     ui  ->  statusbar  ->  showMessage("Saving the file ...");
}
bool textEditor::saveas()
{   QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal)          ;
    dialog.setAcceptMode(QFileDialog::AcceptSave)      ;
    if (dialog.exec() != QDialog::Accepted)
        return false                                   ;
    return save_file(dialog.selectedFiles().first())   ;
    ui  ->  statusbar  ->  showMessage("Saving as ...")        ;
}
void textEditor::set_file(const QString &filename){
    currentFile = filename                              ;
    ui->plainTextEdit->document()->setModified(false)   ;
    setWindowModified(false)                            ;
    QString shownName = currentFile                     ;
    if (currentFile.isEmpty())
        shownName = "untitled.txt"                      ;
    setWindowFilePath(shownName)                        ;
}




