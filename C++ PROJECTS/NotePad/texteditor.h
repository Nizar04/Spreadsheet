#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QSaveFile>



QT_BEGIN_NAMESPACE
namespace Ui { class textEditor; }
QT_END_NAMESPACE

class textEditor : public QMainWindow
{ Q_OBJECT
public:
    textEditor(QWidget *parent = nullptr);~textEditor();
protected:
    void set_file (const QString &filename)  ;
    bool save_file(const QString &filename)  ;
private slots:
    void act_exit()  ;
    void act_new()   ;
    void act_open()  ;
    void act_copy()  ;
    void act_paste() ;
    void act_cut()   ;
    void act_about() ;
    void act_qt()    ;
    bool save()      ;
    bool saveas()    ;

private:
    Ui::textEditor *ui;
    QString currentFile;
};
#endif // TEXTEDITOR_H
