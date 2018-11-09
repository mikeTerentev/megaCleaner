#include "dataparser.h"

dataParser::dataParser(QString const&  dir):rootPath(dir)
{
    //no actions
}

void dataParser::find_dublicate(QString const& dir)
{
   dfs(dir);
}

void dataParser::clear()
{
   isVisited.clear();
   dublicateMap.clear();
}

void dataParser::dfs(QString const& path){
    if (isVisited.contains(path))
    {
      return;
    }
    isVisited.insert(path, true);
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList();
    for (QFileInfo file_info : list)
    {
        if (file_info.fileName() !=".." && file_info.fileName() !=".")
        {
            if (file_info.isDir())
            {
                dfs(file_info.absoluteFilePath());
            }
            else
            {
               QString fileHash = getHash(file_info);
               if (fileHash == "") continue;
               if (dublicateMap.contains(fileHash))
               {
                   dublicateMap.find(fileHash).value().append(file_info);
               }
               else
               {
                   dublicateMap.insert(fileHash,QVector<QFileInfo>({file_info}));
               }
            }
        }

    }
}

QString dataParser::getHash(QFileInfo & file_info){

        QFile file(file_info.absoluteFilePath());
        QCryptographicHash hashAlgo(QCryptographicHash::Sha512);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox msg(QMessageBox::Information, "Msg",
                            "Can't open \n\n" + file_info.absoluteFilePath(), QMessageBox::Ok);
            return "";
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QByteArray byteline;
            byteline.append(in.readLine());
            hashAlgo.addData(byteline);
        }
        QString hash(hashAlgo.result());
        return hash;
}
