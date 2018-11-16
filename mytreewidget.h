#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H


#include <action.h>
#include <qcommonstyle.h>
#include <qtreewidget.h>
#include "dataparser.h"
#include "QKeyEvent"
#include "mainwindow.h"
#include <qdesktopservices.h>
#include <qdebug.h>
class MyTreeWidget : public QTreeWidget {
    Q_OBJECT
public:
    const int SIZE_COL = 2;
    const int DIR_COL = 1;
    const int NAME_COL = 0;

    virtual ~MyTreeWidget(){}

   explicit MyTreeWidget(QWidget *parent = nullptr):QTreeWidget (parent) {

    }
    void setMainWindow(main_window* mw){
         mainwindow = mw;
    }
    void makeFileSystem();

    void removeFile(QTreeWidgetItem *child);

    void scan_directory(const QString &dir);
    QString getItemName(QTreeWidgetItem *item);

    QString getCurrDir() {
        return currentDir;
    }

    QTreeWidgetItem *getSelectedFile() {
        return selectedFile;
    }

    void setCurDir(QString x) {
        currentDir = x;
    }

    void setModeType(bool b) {
        isCurMain = b;
    }

    bool getModeType(){
        return isCurMain;
    }

    void setSelectedFile(QTreeWidgetItem *x) {
        selectedFile = x;
    }

 public
    slots:
            void onTreeWidgetClicked();

            void deleteDublicate(ACTION action);

            void fileSelected(QTreeWidgetItem *curFile);

            void keyPressEvent(QKeyEvent *event);
private:
    main_window* mainwindow;
    QCommonStyle style;
    QString currentDir = QDir::homePath();
    QTreeWidgetItem *selectedFile = nullptr;
    bool isCurMain = true;

    bool checkItem(ACTION action);

    void noDublicatesMessage(const QString &dir);

    void setItemParameters(QTreeWidgetItem *item, QFileInfo &file_info);
};

#endif // MYTREEWIDGET_H
