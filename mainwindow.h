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
#include <thread>
#include <QKeyEvent>
namespace Ui {
    class MainWindow;
}

class main_window : public QMainWindow  {
    Q_OBJECT

public:
    enum ACTION {
        THIS, EXCEPT_THIS
    };
    const int SIZE_COL = 2;
    const int DIR_COL = 1;
    const int NAME_COL = 0;

    explicit main_window(QWidget *parent = nullptr);

    ~main_window();



    public
    slots:
   // void keyPressEvent(QKeyEvent *event);
            void
    removeFile(QTreeWidgetItem
    *child);

    void makeItemUnique();

    void deleteCurrent();

private
    slots:
            void

    makeFileSystem();

    void select_directory();

    void scan_directory(QString const &dir);

    void show_about_dialog();

    void onTreeWidgetClicked();

    void fileSelected(QTreeWidgetItem *);

private:
    bool isCurMain = true;

    void deleteDublicate(ACTION action);

    QString getItemName(QTreeWidgetItem *item);

    void noDublicatesMessage(QString const &dir);

    void genButtoms(bool isMainWindow);

    void setItemParameters(QTreeWidgetItem *item, QFileInfo &file_info);

    QCommonStyle style;
    QString currentDir;
    QTreeWidgetItem *selectedFile = nullptr;
    std::unique_ptr <Ui::MainWindow> ui;

    bool checkItem(ACTION action);
};

#endif // MAINWINDOW_H
