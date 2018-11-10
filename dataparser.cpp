#include "dataparser.h"

DataParser::DataParser(QString const &dir) : rootPath(dir) {
    //no actions
}

DataParser::DataParser() {
    //no actions
}

void DataParser::setDir(QString const &dir) {
    rootPath = dir;
}

void DataParser::find_dublicate(QString const &dir) {
    setDir(dir);
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo  file(it.next());
        if (file.fileName() == ".." && file.fileName() == ".")
            continue;
        if (dublicateSizeMap.contains(file.size())) {
            dublicateSizeMap.find(file.size()).value().append(file.absoluteFilePath());
        } else {
            dublicateSizeMap.insert(file.size(), QVector<QString>({file.absoluteFilePath()}));
        }
    }
    for (auto currGroup : dublicateSizeMap){
        for (auto fileDir : currGroup){
            QFileInfo file_info(fileDir);
            QString fileHash = getHash(fileDir);
            if (fileHash == "") continue;
            if (dublicateMap.contains(fileHash)) {
                dublicateMap.find(fileHash).value().append(file_info);
            } else {
                dublicateMap.insert(fileHash, QVector<QFileInfo>({file_info}));
            }
        }
    }
}

void DataParser::clear() {
    isVisited.clear();
    dublicateMap.clear();
}


//strace fdupes
QString DataParser::getHash(QString &filedir) {
    QFile file_info(filedir);
    QCryptographicHash hashAlgo(QCryptographicHash::Md5);
    if (!file_info.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msg(QMessageBox::Information, "Msg",
                        "Can't open \n\n" + filedir, QMessageBox::Ok);
        return "";
    }
     QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
     hash.addData(&file_info);
     return QString(hash.result());

}
