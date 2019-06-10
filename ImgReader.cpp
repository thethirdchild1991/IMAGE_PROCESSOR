#include "ImgReader.h"
#include <QImageReader>
#include <mutex>

ImgReader::ImgReader( ImgQueueSharedPointer_t queue ) : mQueue(queue)
{

}

ImgReader::ImgReader(QString folderPath) : mFolder(folderPath)
{

}

void ImgReader::doWork( QString path ){


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
            ImageSharedPointer_t pImg = std::make_shared<QImage>( qimr.read() );

            queMutex.lock();
            mQueue->enqueue( pImg );
            queMutex.unlock();

            emit newImage( pImg );

            QThread::msleep( uint32_t(1000)/mFreq );
        }
}

void ImgReader::setFolderPath( QString path ){
    mFolder = QDir(path);
}

void ImgReader::frequency( uint8_t freq ){
    mFreq = freq;
}
