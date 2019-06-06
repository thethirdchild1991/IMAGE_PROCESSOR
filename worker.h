#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QDir>
#include <QImage>

class Worker : public QThread
{    

public:
    explicit Worker( QString folderPath );

    void run() override;

private:
    QDir mFolder;
    QImage* mImage;

};

#endif // WORKER_H
