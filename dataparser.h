#ifndef DATA_SECTION_H
#define DATA_SECTION_H

#include "mainwindow.h"

#include <qfileinfo.h>
#include <qstring.h>
#include <qmap.h>
#include <qcryptographichash.h>
#include <qdiriterator.h>
#include <qmessagebox.h>
#include <mainwindow.h>
#include <qdebug.h>
class DataParser:public QObject {
    Q_OBJECT
public:
    DataParser(QString const &dir,main_window* mainwindow) : mainwindow(mainwindow),rootPath(dir) {
        //no actions
    }

//GETTER
    inline QMap <QByteArray, QVector<QString>> getDublicateMap() {
        return dublicateMap;
    }

    DataParser();

    void setDir(const QString &dir);

private:
    void clear();
    QByteArray getHash(QString &file_info);

private:
    main_window* mainwindow;
    QMap <QByteArray, QVector<QString>> dublicateMap;
    QMap <qint64, QVector<QString>> dublicateSizeMap;
    QString rootPath;
    public
         slots:
    void find_dublicate(QString const &dir);
};

#endif // DATA_SECTION_H
