#ifndef WORKER_H
#define WORKER_H

#include <QDir>
#include "common.h"
#include <mutex>


class ImgReader : public QObject
{    
    Q_OBJECT

public:
    explicit ImgReader( ImgQueueSharedPointer_t queue );
    explicit ImgReader( QString folderPath );

    void frequency( uint8_t freq );


    signals:
    void newImage( ImageSharedPointer_t pImg );

    public slots:
    void setFolderPath( QString path );
    void doWork( QString path );


private:
    QDir mFolder;    
    ImgQueueSharedPointer_t mQueue = nullptr;
    std::mutex queMutex;

    uint8_t mFreq = 60;



};


#endif // WORKER_H
