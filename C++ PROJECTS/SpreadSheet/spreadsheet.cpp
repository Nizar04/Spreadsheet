#include "spreadsheet.h"
#include <QPixmap>
#include <QMessageBox>
#include <QStatusBar>
#include "godialog.h"
#include "finddialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QSettings>
#include <QApplication>
#include <QLineEdit>

SpreadSheet::SpreadSheet(QWidget *parent): QMainWindow(parent)
{
    //Main window
    spreadsheet = new QTableWidget   ;
    spreadsheet->setRowCount(200)    ;
    spreadsheet->setColumnCount(100) ;
    setCentralWidget(spreadsheet)    ;

    createMenus()   ;
    createActions() ;
    createtoolbar() ;
    makeconnexions();

    //creating the labels for the satus bar (should be in its proper function)
    celllocation  = new QLabel("A4")                   ;
    cellformula   = new QLabel("")                     ;
    statusBar()  ->  addPermanentWidget(celllocation)  ;
    statusBar()  ->  addPermanentWidget(cellformula)   ;

   QStringList labels;
   for(char letter = 'A'; letter<= 'Z'; letter++){
       labels << QString{letter};
                                                 }

   spreadsheet  ->  setVerticalHeaderLabels(labels)    ;

   //Initier le champ currentFile
   currentFile    = nullptr ;
   setWindowTitle("Buffer") ;

}

SpreadSheet::~SpreadSheet()
{
    delete spreadsheet     ;
    delete  newfile        ;
    delete savefile        ;
    delete open            ;
    delete cutfile         ;
    delete quit            ;
    delete aboutme         ;
    delete aboutqt         ;
    delete saveas          ;
    delete population      ;
    delete report          ;
    delete Copy            ;
    delete Paste           ;
    delete find            ;
    delete del             ;
    delete gotocell        ;
    delete recalculate     ;
    delete sort            ;
    delete row             ;
    delete column          ;
    delete all             ;
    delete showgrid        ;
    delete autorecalculate ;
    delete search          ;
    delete filemenu        ;
    delete helpmenu        ;
    delete tools           ;
    delete options         ;
    delete edit            ;
    delete select          ;
    delete celllocation    ;
    delete cellformula     ;
    delete currentFile     ;
}

void SpreadSheet::createActions(){


    // Chosing Icons
    QPixmap quitIcon   (":/icons/quit_icon.png")       ;
    QPixmap newIcon    (":/icons/new_file.png")        ;
    QPixmap cutIcon    (":/icons/cut_icon.png")        ;
    QPixmap searchIcon (":/icons/search_icon.png")     ;
    QPixmap saveIcon   (":/icons/save_icon.png")       ;
    QPixmap saveAsIcon (":/icons/saveas.png")          ;
    QPixmap copyIcon   (":/icons/copy.jpg")            ;
    QPixmap pasteIcon  (":/icons/paste.png")           ;
    QPixmap openIcon   (":/icons/open.jpg")            ;
    // Creating Actions
    quit         = new QAction(quitIcon, "&Quit", this)            ;
    savefile     = new QAction(saveIcon, "&Save", this)            ;
    saveas       = new QAction(saveAsIcon,"&Save &As...", this )   ;
    population   = new QAction(copyIcon,"&1 population.sp", this)  ;
    report       = new QAction("&2 Report 2006.sp", this)          ;
    Copy         = new QAction(copyIcon ,"&Copy", this)            ;
    Paste        = new QAction(pasteIcon,"&Paste", this)           ;
    find         = new QAction("&Find", this)                      ;
    gotocell     = new QAction("&Go to Cell", this)                ;
    del          = new QAction("&Delete", this)                    ;
    row          = new QAction("&Row", this)                       ;
    all          = new QAction("&All", this)                       ;
    recalculate  = new QAction("&Recalculate", this)               ;
    sort         = new QAction("&Sort", this)                      ;
    showgrid     = new QAction("&Show Grid",this)                  ;
    showgrid  ->  setCheckable(true)                               ;
    showgrid  ->  setChecked(spreadsheet->showGrid())              ;
/****/

    autorecalculate = new QAction("&Auto-recalculate" , this)      ;
    autorecalculate  ->  setCheckable(true)                        ;

    newfile         = new QAction(newIcon, "&New"     , this)      ;
    cutfile         = new QAction(cutIcon, "&Cut"     , this)      ;
    search          = new QAction(searchIcon,"&Search", this)      ;
    aboutme         = new QAction("&About"            , this)      ;
    aboutqt         = new QAction("&About Qt"         , this)      ;
    open            = new QAction("&Open"             , this)      ;

//setiing shortcuts
    quit         ->       setShortcut(tr("Ctrl+Q"))  ;
    newfile      ->       setShortcut(tr("Ctrl+N"))  ;
    cutfile      ->       setShortcut(tr("Ctrl+U"))  ;
    search       ->       setShortcut(tr("Ctrl+S"))  ;
    Paste        ->       setShortcut(tr("Ctrl+V"))  ;
    Copy         ->       setShortcut(tr("Ctrl+C"))  ;
    del          ->       setShortcut(tr("Del"))     ;
    gotocell     ->       setShortcut(tr("F5"))      ;
    all          ->       setShortcut(tr("Ctrl+A"))  ;
    recalculate  ->       setShortcut(tr("F9"))      ;
    open         ->       setShortcut(tr("Ctrl+O"))  ;

}

void SpreadSheet::createMenus(){

    filemenu = menuBar()->addMenu("&File")        ;
    filemenu    ->  addAction(newfile)            ;
    filemenu    ->  addAction(open)               ;
    filemenu    ->  addAction(savefile)           ;
    filemenu    ->  addAction(saveas)             ;
    filemenu    ->  addSeparator()                ;
    filemenu    ->  addAction(population)         ;
    filemenu    ->  addAction(report)             ;
    filemenu    ->  addSeparator()                ;
    filemenu    ->  addAction(quit)               ;

    edit        = menuBar()->addMenu("&Edit")     ;
    edit        ->addAction(cutfile)              ;
    edit        ->addAction(Copy)                 ;
    edit        ->addAction(Paste)                ;
    edit        ->addAction(del)                  ;

    select = edit  ->  addMenu("&Select")   ;
    select         ->  addAction(row)       ;
    select         ->  addAction(column)    ;
    select         ->  addAction(all)       ;
    edit           ->  addSeparator()       ;
    edit           ->  addAction(find)      ;
    edit           ->  addAction(gotocell)  ;


    tools = menuBar()  ->  addMenu("&Tools")      ;
    tools  ->              addAction(recalculate) ;
    tools  ->              addAction(sort)        ;


    options = menuBar()    ->  addMenu("&Options")         ;
    options                ->  addAction(showgrid)         ;
    options                ->  addAction(autorecalculate)  ;




    helpmenu = menuBar()    ->  addMenu("&Help");
    helpmenu                ->  addAction(aboutme);
    helpmenu                ->  addAction(aboutqt);


}

void SpreadSheet::aboutqtslot(){
    QMessageBox::aboutQt(this, "About Me");
}

void SpreadSheet::createtoolbar(){
    auto toolbar1 =          addToolBar("Tool Bar 1")  ;
    toolbar1      ->         addAction(quit)           ;
    toolbar1      ->         addAction(cutfile)        ;
    auto toolbar2 =          addToolBar("Tool Bar 2")  ;
    toolbar2      ->         addAction(aboutqt)        ;
}

void SpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0,%1)"}                             ;
    celllocation->setText(cell.arg(row+1).arg(col+1))   ;
    statusBar()->showMessage("Opening File", 5000 )     ;
}

void SpreadSheet::makeconnexions(){
    connect(spreadsheet, &QTableWidget::cellClicked, this,        &SpreadSheet::updateStatusBar ) ;
    connect(quit       , &QAction::triggered,        this,        &QMainWindow::close)            ;
    connect(aboutqt    , &QAction::triggered,        this,        &SpreadSheet::aboutqtslot)      ;
    connect(cutfile    , &QAction::triggered,        spreadsheet, &QTableWidget::clear)           ;
    connect(all        , &QAction::triggered,        spreadsheet, &QTableWidget::selectAll)       ;

    connect(showgrid, &QAction::triggered, spreadsheet, &QTableWidget::setShowGrid)  ;
    //Connecting 'go to cell' to the slot 'goCellSlot'
    connect(gotocell, &QAction::triggered, this, &SpreadSheet::goCellSlot)           ;
    //Connecting 'save' to the slot 'saveSlot'
    connect(find,     &QAction::triggered, this, &SpreadSheet::find_slot)             ;
    //Connecting 'save' to the slot 'saveSlot'
    connect(savefile, &QAction::triggered, this, &SpreadSheet::save_slot)             ;
    //Connecting 'open' to the slot 'loadslot'
    connect(saveas, &QAction::triggered, this , &SpreadSheet::saveascsv_slot)         ;
    connect(open, &QAction::triggered, this, &SpreadSheet::loadfile_slot)             ;
    connect(openthecsv, &QAction::triggered, this, &SpreadSheet::loadcsvfile_slot)    ;

}

void SpreadSheet::goCellSlot()
{
    GoDialog D; // Creating dialog
    auto reply  =  D.exec();

    if( reply == GoDialog::Accepted )
    {
        // Extracting the text
        QString cell = D.getCell()           ;
        //Extracting the lign
        int row =  cell[0].toLatin1()- 'A'   ;
        //Extracting the column
        cell = cell.remove(0,1)              ;
        int col = cell.toInt()-1             ;
        // Changing the cell
        statusBar()->showMessage("Changing cell", 2000)               ;
        spreadsheet->setCurrentCell(row, col)                         ;
     }
}

void SpreadSheet::find_slot(){

    FindDialog dialog;
     auto reply = dialog.exec();
     auto found = false;

     if(reply == FindDialog::Accepted)
     { QString text = dialog.getText();
         for(auto i=0; i<spreadsheet->rowCount(); i++)
         { for(auto j=0; j<spreadsheet->columnCount(); j++)
             { if(spreadsheet->item(i,j))
                 { if(spreadsheet->item(i,j)->text() == text){
                          spreadsheet->setCurrentCell(i,j);
                          found = true;
         }}}}

         if(!found)
             QMessageBox::information(this,"Error","No match") ;
         }
         }

void SpreadSheet::save_slot(){

    //Testing for the existance of a filename
    if(!currentFile){
    //Créer Factory design
    QFileDialog D;
    //Obtaining filename from dialog
    auto filename = D.getSaveFileName()    ;
    //Change current file name
    currentFile   = new QString{filename}  ;
    //Updating the window title
    setWindowTitle(*currentFile)           ;
    }
    save_content(*currentFile);
}
void SpreadSheet::saveascsv_slot() {
//Testing the existance of filename
if(!currentFile)
{
    //creer Factory design
    QFileDialog d;

    // creer un dialog pour obtenir le nom de fichier
    auto filename = d.getSaveFileName();

    recentFilesList.append(new QAction(filename,this))                              ;
    recentFilesMenu->addAction(recentFilesList[i])                                  ;
    connect(recentFilesList[i],&QAction::triggered,this,&SpreadSheet::openrecent)   ;
    i++;
    //Change current file name
    currentFile = new QString(filename)   ;
    // Updating window title
    setWindowTitle(*currentFile)          ;

}
// sauvegarder le contenu
saveascsv_content(*currentFile)     ;

}

void SpreadSheet::save_content(QString filename)
{

    QFile file(filename);

    //Opening A File in write mode
    if(file.open(QIODevice::WriteOnly))
    { QTextStream out(&file);

        //Saving changes by going thru each cell
       for(int i = 0; i < spreadsheet->rowCount(); i++)
        { for(int j = 0; j < spreadsheet->columnCount(); j++)
            { auto cell = spreadsheet->item(i,j);
                if(cell)
    out << i << " , " << j << " , " << cell->text() <<Qt::endl;
            }}
    }
    file.close();
}
void SpreadSheet::saveascsv_content(QString filename) {
    QFile file(filename);

   int rows = spreadsheet->rowCount();
   int columns = spreadsheet->columnCount();
   if(file.open(QIODevice::WriteOnly )) {
    QTextStream out(&file);
    for (int i = 0; i < rows; i++) {
       for (int j = 0; j < columns; j++) {
           auto cell = spreadsheet->item(i,j);
           if(cell)
               out<< cell->text()<<","       ;
           else
               out<< " "<<","                ;
       }     out<< Qt::endl;   }
file.close();
}
}
void SpreadSheet::loadfile_slot(){

        QFileDialog D;
        auto filename = D.getOpenFileName();

        //ajouter le fichier qu'on vient d'ouvrir a recentFiles et creer la connexion
        recentFilesList.append(new QAction(filename,this));
        recentFilesMenu->addAction(recentFilesList[i]);

        connect(recentFilesList[i],&QAction::triggered,this,&SpreadSheet::openrecent);
                              i++                                                    ;
        if(filemenu)

       {
            currentFile = new QString(filename)   ;
            setWindowTitle(*currentFile)          ;
            open_content(*currentFile)            ;

        }
}
void SpreadSheet::loadcsvfile_slot(){

        QFileDialog D;
        auto filename = D.getOpenFileName()                                            ;
        recentFilesList.append(new QAction(filename,this))                             ;
        recentFilesMenu->addAction(recentFilesList[i])                                 ;
        connect(recentFilesList[i],&QAction::triggered,this,&SpreadSheet::openrecent)  ;
                                                                                  i++  ;
        if(filemenu)

       {            currentFile = new QString(filename)   ;
                    setWindowTitle(*currentFile)          ;
                    open_csv_content(*currentFile)        ;
       }

}
void SpreadSheet::open_content(QString filename)
{
     QFile file(filename);
     if(file.open(QIODevice::ReadOnly))
    {   QTextStream in (&file);
        QString line          ;
          while(!in.atEnd())
          {
            line         =  in.readLine()             ;
            auto tokens  =  line.split(QChar(','))    ;
            int row      =  tokens[0].toInt()         ;
            int column   =  tokens[1].toInt()         ;
            spreadsheet  ->  setItem(row, column, new QTableWidgetItem(tokens[2]))  ;
            }}
            file.close();
}
void SpreadSheet::open_csv_content(QString filename){
         QFile file(filename);
         QStringList list;
         int count = 0;
          if(file.open(QIODevice::ReadOnly))
          { QTextStream in(&file);
               while( !in.atEnd())
               { QString line = in.readLine();
                  for(auto content : line.split(","))
                      list.append(content);
                  for(auto i =0; i<list.length(); i++)
                      spreadsheet->setItem(count,i, new QTableWidgetItem(list[i]));
                 count++;
                 list.clear()  ;
              }}
         file.close()          ;
}

void SpreadSheet::openrecent(){
    QAction *action = qobject_cast<QAction *>(sender()) ;
    if (action)
    {
        open_content      (  action  ->  text())  ;
        save_content      (  action  ->  text())  ;
        saveascsv_content (  action  ->  text())  ;
    }}
void SpreadSheet::copy_slot()
{
     QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
     if (lineEdit)
     {         lineEdit->copy();    }
}
void SpreadSheet::cut_slot()
{
    QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
      if (lineEdit)
      {          lineEdit->cut();      }
}
void SpreadSheet::paste_slot()
{
      QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
      if (lineEdit)
      {       lineEdit->paste();      }
}

