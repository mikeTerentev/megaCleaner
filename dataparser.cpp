#include "dataparser.h"

#include <QProgressDialog>
#include <qthread.h>





DataParser::DataParser() {
    //no actions
}

void DataParser::setDir(QString const &dir) {
    rootPath = dir;
}

void DataParser::find_dublicate() {
    setDir(rootPath);
    int numFiles = 0;
    QDirIterator it(rootPath,QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        if(QThread::currentThread()->isInterruptionRequested()){
            emit finished(QDialog::Accepted);
            return;
        }
        QFileInfo  file =(it.next());
       // qDebug()<<file.absoluteFilePath();
        QString x(file.fileName());
        if (file.isSymLink()) continue;
           dublicateSizeMap[file.size()].push_back(file.absoluteFilePath());
           numFiles++;
    }
    emit filesCounted(numFiles);
    int hashedNum=0;
    for (auto& currGroup : dublicateSizeMap){
        if (currGroup.count() < 2) continue;
        for (auto& fileDir : currGroup){
            if (QThread::currentThread()->isInterruptionRequested()){
                emit finished(QDialog::Accepted);
                return;
            }
            QByteArray fileHash = getHash(fileDir);
            if (fileHash == "") continue;
            dublicateMap[fileHash].push_back(fileDir);
            emit filesChecked(++hashedNum);
        }
    }
    emit finished(QDialog::Accepted);
}

void DataParser::clear() {
    dublicateMap.clear();
}
void  DataParser::stop(){
    isStopped = true;
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
