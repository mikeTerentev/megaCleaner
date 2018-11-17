#include "dataparser.h"

#include <QProgressDialog>





DataParser::DataParser() {
    //no actions
}

void DataParser::setDir(QString const &dir) {
    rootPath = dir;
}

void DataParser::find_dublicate(QString const &dir) {
     setDir(dir);
    setDir(rootPath);
    int numFiles = 0;
   QDirIterator it(rootPath,QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo  file(it.next());
        QString x(file.fileName());
           dublicateSizeMap[file.size()].push_back(file.absoluteFilePath());
           numFiles++;
    }
    for (auto& currGroup : dublicateSizeMap){
        if(currGroup.count() < 2) continue;
        for (auto& fileDir : currGroup){
                QByteArray fileHash = getHash(fileDir);
                dublicateMap[fileHash].push_back(fileDir);

        }
    }
}

void DataParser::clear() {
    dublicateMap.clear();
}


//strace fdupes
QByteArray DataParser::getHash(QString &filedir) {
    QFile file_info(filedir);
    QCryptographicHash hashAlgo(QCryptographicHash::Sha256);
    if (!file_info.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msg(QMessageBox::Information, "Msg",
                        "Can't open \n\n" + filedir, QMessageBox::Ok);
        return nullptr;
    }
     QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
     hash.addData(&file_info);
     return hash.result();
}
