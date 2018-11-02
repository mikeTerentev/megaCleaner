#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCommonStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <memory>
#include <dataparser.h>
namespace Ui {
class MainWindow;
}

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    const int SIZE_COL = 2;
    const int DIR_COL = 1;
    const int NAME_COL = 0;
    explicit main_window(QWidget *parent = nullptr);
    ~main_window();

private slots:
    void makeFileSystem();
    void select_directory();
    void scan_directory(QString const& dir);
    void show_about_dialog();
    void onTreeWidgetClicked(QTreeWidgetItem*);
    void deleteDublicate();
    void fileSelected(QTreeWidgetItem*);
private:
    void noDublicatesMessage(QString const& dir);
    void genButtoms(bool isMainWindow);
    QString currentDir;
    QTreeWidgetItem* selectedFile = nullptr;
    std::unique_ptr<Ui::MainWindow> ui;
};

#endif // MAINWINDOW_H
