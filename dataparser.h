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

class DataParser : public QObject {
Q_OBJECT
public:
    DataParser(QString const &dir) : rootPath(dir) {
        //no actions
    }

//GETTER
    inline QMap<QByteArray, QVector<QString>> getDuplicateMap() {
        return duplicateMap;
    }

    DataParser();

    QByteArray getHash(QString &file_info);

    void setDir(const QString &dir);

    QString rootPath;
private:
    void clear();

private:
    QMap<QByteArray, QVector<QString>> duplicateMap;
    QMap<qint64, QVector<QString>> duplicateSizeMap;

public slots:

    void find_dublicate();

signals:

    void filesCounted(int);

    void filesChecked(int);

    void finished(int);

    void error(QString err);
};

#endif // DATA_SECTION_H
