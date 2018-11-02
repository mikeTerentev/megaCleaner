#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <qdesktopservices.h>
#include <qurl.h>

main_window::main_window(QWidget *parent)
    : ui(new Ui::MainWindow)
    , QMainWindow(parent)
    , currentDir(QDir::homePath())
{
    ui->setupUi(this);
    //setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    ui->treeWidget->header()->setSectionResizeMode(NAME_COL, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(DIR_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSectionResizeMode(SIZE_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    QCommonStyle style;
    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));

    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);
    connect(ui->pushScanDir,SIGNAL(clicked()),this,SLOT(select_directory()));
    connect(ui->pushGoBack,SIGNAL(clicked()),this,SLOT(makeFileSystem()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeWidgetClicked(QTreeWidgetItem*)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(fileSelected(QTreeWidgetItem*)));
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(deleteDublicate()));

    makeFileSystem();
}

void main_window:: fileSelected(QTreeWidgetItem* curFile){
   selectedFile = curFile;
}

void main_window::deleteDublicate(){
    if (selectedFile == nullptr || selectedFile->text(DIR_COL) =="") {
        QMessageBox::warning(this,tr("Select file"),"Select file",QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::warning(this, tr("Deleting"),
                                            "Do you really want to delete dublicates of \n\n"
                                   + selectedFile->text(DIR_COL)+ "/" +selectedFile->text(NAME_COL) ,
                                            QMessageBox::Ok | QMessageBox::Cancel);
     if (ret == QMessageBox::Cancel)
     {
         return;
     }
    QTreeWidgetItem* parent = selectedFile->parent();
    QList<QTreeWidgetItem*> children = parent->takeChildren();
    for (auto child : children){
        if (selectedFile == child)
            continue;
        QString delFilePath  = child->text(DIR_COL) + "/" + child->text(0);
        QFile file(delFilePath);
        if(!file.remove()){
            QMessageBox::warning(this, tr("Can't delete file"),
                                                          "File \n\n" + delFilePath +"\n\n can't be removed.",
                                                         QMessageBox::Ok );
        }
    }
    delete parent;
    QString msg = QString::number(children.size()) + " files was successfuly deleted\n";
    QMessageBox::information(this, tr("Congratulations"), msg, QMessageBox::Ok);

    if (ui->treeWidget->topLevelItemCount() == 0){
       noDublicatesMessage(currentDir);
    }
}

main_window::~main_window()
{}

void main_window::select_directory(){
    scan_directory(currentDir);
}

void main_window::scan_directory(QString const& dir){
    //QMessageBox msg(QMessageBox::Cancel, );
     ui->treeWidget->clear();
    setWindowTitle(QString("Directory Content - %1").arg(dir));
    //Algo
    dataParser s(dir);
    s.find_dublicate(dir);

    //windows processing
    bool isDublicate= false;
    for (QVector<QFileInfo>comp : s.getDublicateMap())
    {
        QCommonStyle style;
        if (comp.size() < 2) continue;
        isDublicate = true;
        QTreeWidgetItem*  group = new QTreeWidgetItem();
        group->setText(0,QString::number(comp.size()) + " dublicated files");
        if(comp.size() * comp.begin()->size() > 1000){
              group->setIcon(NAME_COL,style.standardIcon(QStyle::SP_MessageBoxCritical));
        } else {
            group->setIcon(NAME_COL,style.standardIcon(QStyle::SP_MessageBoxWarning));
        }
        group->setTextColor(0,Qt::red);
        group->setText(SIZE_COL,QString::number(comp.size() * comp.begin()->size()));
        for (QFileInfo file_info : comp)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(NAME_COL, file_info.fileName());
            item->setText(DIR_COL, file_info.path());
            item->setText(SIZE_COL, QString::number(file_info.size()));
            group->addChild(item);
        }
        ui->treeWidget->addTopLevelItem(group);
    }
    ui->treeWidget->sortItems(2,Qt::SortOrder::DescendingOrder);
    genButtoms(false);
    selectedFile = nullptr;
    if (!isDublicate)
    {
        noDublicatesMessage(dir);
    }


}
void main_window::makeFileSystem()
{
    QCommonStyle style;
    ui->treeWidget->clear();
    genButtoms(true);
    setWindowTitle(QString("Directory Content - %1").arg(currentDir));
    QDir d(currentDir);
    QFileInfoList list = d.entryInfoList();
    QList<QTreeWidgetItem *> items;
    for (QFileInfo file_info : list)
    {
        if (file_info.fileName() == "..")  continue;
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            if (file_info.fileName() == ".")
            {
             item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_DialogOkButton));
             //item->setText(DIR_COL, file_info.dir().path());
            }
            else
            {
                if (file_info.isDir())
                {
                    item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_DirIcon));
                }
                else
                {
                    item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_FileIcon));
                }
                item->setText(NAME_COL, file_info.fileName());
                item->setText(DIR_COL, file_info.path());
                item->setText(SIZE_COL, QString::number(file_info.size()));
            }
            items.append(item);
    }
    ui->treeWidget->insertTopLevelItems(0,items);
   //ui->treeWidget->sortItems(SIZE_COL,Qt::SortOrder::DescendingOrder);
}


void main_window::show_about_dialog()
{
    QMessageBox::aboutQt(this);
}

void main_window::onTreeWidgetClicked(QTreeWidgetItem *item){
    QString prevDir = currentDir;
    prevDir.truncate(prevDir.lastIndexOf("/"));
    QString x = item->text(DIR_COL) =="" ?  prevDir : item->text(DIR_COL) + '/' + item->text(NAME_COL);
    QFileInfo tmp(x);
    if(tmp.isDir()){
        currentDir= x;
        makeFileSystem();
    }
}
void main_window::noDublicatesMessage(QString const & dir){
    makeFileSystem();
    QMessageBox msg(QMessageBox::Information, "Msg",
                    "No dublicate files found in directiory:\n\n "+ dir +"\n\nDo you want to exit from application?", QMessageBox::Yes | QMessageBox::No);
       if (msg.exec() == QMessageBox::Yes){
          this->close();
       }
}

void main_window::genButtoms(bool isMainWindow){
        ui->pushGoBack->setVisible(!isMainWindow);
        ui->pushButton->setVisible(!isMainWindow);
        ui->pushScanDir->setVisible(isMainWindow);
}
