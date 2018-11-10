#ifndef DATA_SECTION_H
#define DATA_SECTION_H

#include <QWidget>
#include <QMap>
#include <QFileInfo>
#include <QDir>
#include <QCryptographicHash>
#include <QTextStream>
#include <QtGlobal>
#include <QMessageBox>
#include <QDirIterator>

class DataParser {
public:
    DataParser(QString const &dir);

    void find_dublicate(QString const &dir);

//GETTER
    inline QMap <QString, QVector<QFileInfo>> getDublicateMap() {
        return dublicateMap;
    }

    DataParser();

    void setDir(const QString &dir);

private:
    void clear();

    QString getHash(QString &file_info);

private:
    QMap <QString, QVector<QFileInfo>> dublicateMap;
    QMap <qint64, QVector<QString>> dublicateSizeMap;
    QString rootPath;

};

#endif // DATA_SECTION_H
