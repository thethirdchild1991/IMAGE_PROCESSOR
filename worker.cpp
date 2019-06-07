#include "worker.h"


#include <QDebug>
#include <QFileInfo>
#include <QImageReader>

Worker::Worker(){

}

Worker::Worker(QString folderPath) : mFolder(folderPath)
{

}

void Worker::doWork( QString path ){


    setFolderPath(path);

    qDebug() << "doWork: " << path;

    if(!mFolder.exists())
        return;

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    mFolder.setNameFilters( filters );
    mFolder.setSorting( QDir::Name );

    auto filenamesList = mFolder.entryList();

//    while(1)
        for(const auto& filename : filenamesList){

            QImageReader qimr( mFolder.path() + QDir::separator() + filename);

            emit newImage( std::make_shared<QImage>( qimr.read() ) );

            QThread::msleep( uint32_t(1000)/mFreq );
        }
}

void Worker::setFolderPath( QString path ){
    mFolder = QDir(path);
}
