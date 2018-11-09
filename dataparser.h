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
class dataParser
{
public:
    dataParser(QString const& dir);
    void find_dublicate(QString const& dir);
//GETTER
    inline QMap<QString, QVector<QFileInfo>> getDublicateMap(){
        return dublicateMap;
    }

private:
    void clear();
    void dfs(QString const& path);
    QString getHash(QFileInfo &file_info);

private:

    QMap<QString, bool> isVisited;
    QMap<QString, QVector<QFileInfo>> dublicateMap ;
    QString rootPath;

};

#endif // DATA_SECTION_H
