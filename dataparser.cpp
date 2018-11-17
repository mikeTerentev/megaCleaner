#include "dataparser.h"

#include <QProgressDialog>





DataParser::DataParser() {
    //no actions
}

void DataParser::setDir(QString const &dir) {
    rootPath = dir;
}

void DataParser::find_dublicate() {
    setDir(rootPath);
    int numTasks = 0;
    int numFiles = 0;
    QDirIterator it(rootPath, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo  file(it.next());
        QString x(file.fileName());
        if ( x == ".." && x == ".")
            continue;
        if (dublicateSizeMap.contains(file.size())){
            numTasks++;
        }
           dublicateSizeMap[file.size()].push_back(file.absoluteFilePath());
           numFiles++;
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
