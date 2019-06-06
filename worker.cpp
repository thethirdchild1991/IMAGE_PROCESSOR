#include "worker.h"


#include <QDebug>
#include <QImageReader>

Worker::Worker(QString folderPath) : mFolder(folderPath)
{

}

void Worker::run (){

    mFolder.setFilter( QDir::Files );
    mFolder.setSorting( QDir::Name );

    auto filenamesList = mFolder.entryList();

    while(1)
    for(auto filename : filenamesList){
        qDebug() << filename;
        QImageReader qimr(filename);
        mImage = new QImage(qimr.read());
        delete mImage;
        QThread::msleep(16);
    }
}
