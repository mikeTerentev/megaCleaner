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
    DataParser(QString const &dir) : rootPath(dir) {
        //no actions
    }

//GETTER
    inline QMap <QByteArray, QVector<QString>> getDublicateMap() {
        return dublicateMap;
    }
    DataParser();
    void setDir(const QString &dir);
     QString rootPath;
     void stop();
private:
    DataParser* worker;
    QThread* thread;
    void clear();
    QByteArray getHash(QString &file_info);

private:
    bool isStopped = false;
    QMap <QByteArray, QVector<QString>> dublicateMap;
    QMap <qint64, QVector<QString>> dublicateSizeMap;

public slots:
    void find_dublicate();
signals:
    void filesCounted(int);
    void filesChecked(int);
    void finished(int);
    void error(QString err);
};

#endif // DATA_SECTION_H
