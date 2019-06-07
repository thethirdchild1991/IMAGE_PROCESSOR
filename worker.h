#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QDir>
#include <QImage>
#include <memory>

using ImageSharedPointer_t = std::shared_ptr<QImage>;

class Worker : public QObject
{    
    Q_OBJECT

public:
    Worker();
    explicit Worker( QString folderPath );


    signals:
    void newImage( ImageSharedPointer_t pImg );

    public slots:
    void setFolderPath( QString path );
    void doWork( QString path );


private:
    QDir mFolder;
    QImage* mImage;

    uint8_t mFreq = 2;

};

Q_DECLARE_METATYPE( ImageSharedPointer_t );
#endif // WORKER_H
