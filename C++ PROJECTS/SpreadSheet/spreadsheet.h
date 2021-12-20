#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QCoreApplication>
#include <QWidget>
#include <QLabel>
#include <QApplication>
class SpreadSheet : public QMainWindow
{
    Q_OBJECT

public:
    SpreadSheet(QWidget *parent = nullptr);~SpreadSheet();
    int i  =  0                                          ;
protected:
    void createActions()                          ;
    void createMenus()                            ;
    void createtoolbar()                          ;
    void updatestatusbar()                        ;
    void makeconnexions()                         ;
    void save_content(QString filename)           ;
    void saveascsv_content(QString filename)      ;
    void open_content(QString filename)           ;
    void open_csv_content(QString filename)       ;

private:
    QTableWidget   *spreadsheet     ;
    QAction        *newfile         ;
    QAction        *savefile        ;
    QAction        *open            ;
    QAction        *cutfile         ;
    QAction        *quit            ;
    QAction        *aboutme         ;
    QAction        *aboutqt         ;
    QAction        *saveas          ;
    QAction        *openthecsv      ;
    QAction        *population      ;
    QAction        *report          ;
    QAction        *Copy            ;
    QAction        *Paste           ;
    QAction        *find            ;
    QAction        *del             ;
    QAction        *gotocell        ;
    QAction        *recalculate     ;
    QAction        *sort            ;
    QAction        *row             ;
    QAction        *column          ;
    QAction        *all             ;
    QAction        *showgrid        ;
    QAction        *autorecalculate ;
    QAction        *search          ;

    QMenu          *filemenu        ;
    QMenu          *helpmenu        ;
    QMenu          *tools           ;
    QMenu          *options         ;
    QMenu          *edit            ;
    QMenu          *select          ;
    QMenu          *recentFilesMenu ;

    QLabel         *celllocation    ;
    QLabel         *cellformula     ;
    QString        *currentFile     ;
    QList<QAction*> recentFilesList ;


private slots:
  void aboutqtslot()               ;
  void updateStatusBar(int,int)    ;
  void goCellSlot()                ;
  void find_slot()                 ;
  void save_slot()                 ;
  void saveascsv_slot()            ;
  void loadfile_slot()             ;
  void openrecent()                ;
  void loadcsvfile_slot()          ;
  void copy_slot()                 ;
  void cut_slot()                  ;
  void paste_slot()                ;
  void save_content()              ;






};
#endif // SPREADSHEET_H
