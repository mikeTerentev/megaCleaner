#include "mainwindow.h"
#include "ui_mainwindow.h"



main_window::main_window(QWidget *parent)
        : ui(new Ui::MainWindow), QMainWindow(parent) {
    ui->setupUi(this);

    ui->treeWidget->header()->setSectionResizeMode(ui->treeWidget->NAME_COL, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(ui->treeWidget->DIR_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSectionResizeMode(ui->treeWidget->SIZE_COL, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));

    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)), ui->treeWidget,
            SLOT(onTreeWidgetClicked()));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem * , int)), ui->treeWidget, SLOT(fileSelected(QTreeWidgetItem * )));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem * )), ui->treeWidget,
            SLOT(fileSelected(QTreeWidgetItem * )));


    connect(ui->pushScanDir, SIGNAL(clicked()), this, SLOT(select_directory()));
    connect(ui->pushGoBack, SIGNAL(clicked()), this, SLOT(makeFileSystem()));
    connect(ui->pushMakeItemUnique, SIGNAL(clicked()), this, SLOT(makeItemUnique()));
    connect(ui->pushDeleteCurrent, SIGNAL(clicked()), this, SLOT(deleteCurrent()));
    makeFileSystem();
}

main_window::~main_window() {}


void main_window::makeItemUnique() {
    ui->treeWidget->setSelectedFile(ui->treeWidget->currentItem());
    ui->treeWidget->deleteDublicate(ACTION::EXCEPT_THIS);
}

void main_window::deleteCurrent() {
    ui->treeWidget->deleteDublicate(ACTION::THIS);
}

void main_window::makeFileSystem() {
    genButtoms(true);
    ui->treeWidget->makeFileSystem();
}

void main_window::select_directory() {
    ui->treeWidget->scan_directory(ui->treeWidget->getCurrDir());
    genButtoms(false);
}


void main_window::show_about_dialog() {
    QMessageBox::aboutQt(this);
}

void main_window::genButtoms(bool isMainWindow) {
    ui->pushGoBack->setVisible(!isMainWindow);
    ui->pushMakeItemUnique->setVisible(!isMainWindow);
    ui->pushDeleteCurrent->setVisible(!isMainWindow);
    ui->pushScanDir->setVisible(isMainWindow);
    isCurMain = isMainWindow;
    ui->treeWidget->setModeType(isMainWindow);
}
