
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
     /*QString path = "/Users/miketerentyev/itmo/Tests";
    dataParser s(path);
    s.find_dublicate(path);
    QMap<QString, QVector<QFileInfo>> resultMap = s.getDublicateMap();
   */
    main_window w;
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Mega Cleaner");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dontUseCustomDirectoryIconsOption("c", "Set QFileIconProvider::DontUseCustomDirectoryIcons");
    w.show();
    return app.exec();
}
