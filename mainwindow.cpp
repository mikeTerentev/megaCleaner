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
    QCommonStyle style;
    //Tree preferences
    ui->treeWidget->header()->setSectionResizeMode(NAME_COL, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(DIR_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSectionResizeMode(SIZE_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));


    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);

    //TreeConnection
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeWidgetClicked(QTreeWidgetItem*)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(fileSelected(QTreeWidgetItem*)));
     //connect(ui->treeWidget, SIGNAL(itemEntered(QTreeWidgetItem*,int)), this, SLOT(onTreeWidgetClicked(QTreeWidgetItem*)));
    //ButtonsConnection
    connect(ui->pushScanDir,SIGNAL(clicked()),this,SLOT(select_directory()));
    connect(ui->pushGoBack,SIGNAL(clicked()),this,SLOT(makeFileSystem()));
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(deleteDublicate()));

    makeFileSystem();
}

main_window::~main_window()
{}

void main_window::makeFileSystem()
{
    QCommonStyle style;
    ui->treeWidget->clear();
    genButtoms(true);
    setWindowTitle(QString("Directory Content - %1").arg(currentDir));
    QDir d(currentDir);
    QFileInfoList list = d.entryInfoList();
    QList<QTreeWidgetItem *> items;
    for (QFileInfo file_info : list){
        if (file_info.fileName() == "..")
            continue;
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            if (file_info.fileName() == "."){
             item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_DialogOkButton));
            }
            else{
                file_info.isDir() ? item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_DirIcon)) : item->setIcon(NAME_COL,style.standardIcon(QStyle::SP_FileIcon));
                setItemParameters(item,file_info);
            }
            items.append(item);
    }
    ui->treeWidget->insertTopLevelItems(0,items);
}


void main_window::deleteDublicate(){
    if (selectedFile == nullptr || selectedFile->text(DIR_COL) =="") {
        QMessageBox::warning(this,tr("Select file"),"Select file",QMessageBox::Ok);
        return;
    }
    if (QMessageBox::warning(this, tr("Deleting"),
                       "Do you really want to delete dublicates of \n\n" + getItemName(selectedFile) ,
                            QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel){
        return;
    }

    QTreeWidgetItem* parent = selectedFile->parent();
    QList<QTreeWidgetItem*> children = parent->takeChildren();
    for (auto child : children){
        if (selectedFile == child)
            continue;
        QString delFilePath  = getItemName(child);
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



void main_window::select_directory(){
    scan_directory(currentDir);
}

void main_window::scan_directory(QString const& dir){
    ui->treeWidget->clear();
    setWindowTitle(QString("Directory Dublicate Content - %1").arg(dir));
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
        comp.size() * comp.begin()->size() > 1000 ? group->setIcon(NAME_COL,style.standardIcon(QStyle::SP_MessageBoxCritical)) : group->setIcon(NAME_COL,style.standardIcon(QStyle::SP_MessageBoxWarning));
        group->setText(NAME_COL,QString::number(comp.size()) + " dublicated files");
        group->setTextColor(NAME_COL,Qt::red);
        group->setText(SIZE_COL,QString::number(comp.size() * comp.begin()->size()));
        for (QFileInfo file_info : comp)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            setItemParameters(item,file_info);
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



void main_window::show_about_dialog()
{
    QMessageBox::aboutQt(this);
}

void main_window::onTreeWidgetClicked(QTreeWidgetItem *item){
    QString prevDir = currentDir;
    prevDir.truncate(prevDir.lastIndexOf("/"));
    QString newOdj = item->text(DIR_COL) =="" ?  prevDir : getItemName(item);
    QFileInfo tmp(newOdj);
    if(tmp.isDir()){
        currentDir= newOdj;
        makeFileSystem();
    }
}



void main_window::noDublicatesMessage(QString const & dir){
    makeFileSystem();
    if ( QMessageBox::information(this, "Msg",
        "No dublicated files found in directiory:\n\n "+ dir +"\n\nDo you want to exit from application?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        this->close();
    }
}

void main_window:: fileSelected(QTreeWidgetItem* curFile){
   selectedFile = curFile;
}

void main_window::genButtoms(bool isMainWindow){
        ui->pushGoBack->setVisible(!isMainWindow);
        ui->pushButton->setVisible(!isMainWindow);
        ui->pushScanDir->setVisible(isMainWindow);
}

QString main_window::getItemName(QTreeWidgetItem *item){
    return  item->text(DIR_COL) + '/' + item->text(NAME_COL);
}
void main_window::setItemParameters(QTreeWidgetItem *item,QFileInfo& file_info){
    item->setText(NAME_COL, file_info.fileName());
    item->setText(DIR_COL, file_info.path());
    item->setText(SIZE_COL, QString::number(file_info.size()));
}
