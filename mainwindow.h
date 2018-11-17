#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>
#include <qmainwindow.h>
#include <qcommonstyle.h>


namespace Ui {
    class MainWindow;
}

class main_window : public QMainWindow {
    Q_OBJECT

public:


    explicit main_window(QWidget *parent = nullptr);

    ~main_window();


public
    slots:

    void deleteCurrent();

    void makeItemUnique();

    void scan_directory();

    void  makeFileSystem();
    private
    slots:

    void show_about_dialog();   


private:
    bool isCurMain = true;

    void genButtoms(bool isMainWindow);

    QCommonStyle style;

    std::unique_ptr <Ui::MainWindow> ui;
};

#endif // MAINWINDOW_H
