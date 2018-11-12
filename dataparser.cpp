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
        QString x(file.fileName());
        if ( x == ".." && x == ".")
            continue;
            dublicateSizeMap[file.size()].push_back(file.absoluteFilePath());
    }
    for (auto& currGroup : dublicateSizeMap){
        for (auto& fileDir : currGroup){
            QString fileHash = getHash(fileDir);
            if (fileHash == "") continue;
            dublicateMap[fileHash].push_back(fileDir);
        }
    }
}

void DataParser::clear() {
    dublicateMap.clear();
}


//strace fdupes
QString DataParser::getHash(QString &filedir) {
    QFile file_info(filedir);
    QCryptographicHash hashAlgo(QCryptographicHash::Md5);
    if (!file_info.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msg(QMessageBox::Information, "Msg",
                        "Can't open \n\n" + filedir, QMessageBox::Ok);
        return QString("");
    }
     QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
     hash.addData(&file_info);
     return hash.result();
}
