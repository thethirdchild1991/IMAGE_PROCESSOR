#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <QObject>
#include <common.h>

class ImgProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ImgProcessor(QObject *parent = nullptr);
    explicit ImgProcessor( ImgQueueSharedPointer_t queue );

    void ProcessTime( uint32_t time );


//signals:

public slots:
    void checkSize();

private:
    ImgQueueSharedPointer_t mQueue = nullptr;
    uint32_t mProcesTime;

};

#endif // IMGPROCESSOR_H
