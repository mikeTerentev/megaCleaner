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
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private slots:
    void makeFileSystem(QString const& dir);
    void select_directory();
    void scan_directory(QString const& dir);
    void show_about_dialog();
    void onTreeWidgetClicked(QTreeWidgetItem*, int);
private:
    std::unique_ptr<Ui::MainWindow> ui;
};

#endif // MAINWINDOW_H
