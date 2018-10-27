#include "mainwindow.h"
#include "ui_mainwindow.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    QCommonStyle style;
    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));

    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);
    connect(ui->pushScanDir,SIGNAL(clicked()),this,SLOT(select_directory()));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeWidgetClicked(QTreeWidgetItem*,int)));

    makeFileSystem(QDir::homePath());
}

main_window::~main_window()
{}

void main_window::select_directory()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning",
                                                    QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty())
    {
        return;
    }
    scan_directory(dir);
}

void main_window::scan_directory(QString const& dir){
    //QMessageBox msg(QMessageBox::Cancel, );

     ui->treeWidget->clear();
    setWindowTitle(QString("Directory Content - %1").arg(dir));
    dataParser s(dir);
    s.find_dublicate(dir);
    bool isDublicate= false;
    for (QVector<QFileInfo>comp : s.getDublicateMap())
    {
        if (comp.size() < 2) continue;
        isDublicate = true;
        QTreeWidgetItem*  group = new QTreeWidgetItem();
        group->setText(0,QString::number(comp.size()) + " dublicated files");
        group->setTextColor(0,Qt::red);
        for (QFileInfo file_info : comp)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0, file_info.fileName());
            item->setText(1, file_info.path());
            item->setText(2, QString::number(file_info.size()));
            group->addChild(item);
        }
        ui->treeWidget->addTopLevelItem(group);
    }
    ui->treeWidget->sortItems(0,Qt::SortOrder::DescendingOrder);
    if (!isDublicate)
    {
        makeFileSystem(QDir::homePath());
        QMessageBox msg(QMessageBox::Information, "Msg",
                        "No dublicate files found in directiory:\n "+dir+"\n\nDo you want to exit from application?", QMessageBox::Yes | QMessageBox::No);
           if (msg.exec() == QMessageBox::Yes){
              this->close();
           }
    }


}
void main_window::makeFileSystem(QString const& dir)
{
    ui->treeWidget->clear();
    setWindowTitle(QString("Directory Content - %1").arg(dir));
    QDir d(dir);
    QFileInfoList list = d.entryInfoList();
    for (QFileInfo file_info : list)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, file_info.fileName());
        item->setText(1, file_info.path());
        item->setText(2, QString::number(file_info.size()));
        ui->treeWidget->addTopLevelItem(item);
    }
}


void main_window::show_about_dialog()
{
    QMessageBox::aboutQt(this);
}

void main_window::onTreeWidgetClicked(QTreeWidgetItem *item, int col){
    QString x = item->text(1) + '/' + item->text(0);
    makeFileSystem(x);
}
/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTreeView tree;
    QFileSystemModel model;
    model.setRootPath("");
    model.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
    tree.setModel(&model);
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            tree.setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features

    tree.setWindowTitle(QObject::tr("Dir View"));

    QWidget* window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(tree);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_pushButton_2_clicked()
{

}*/
