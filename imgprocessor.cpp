#include "imgprocessor.h"

ImgProcessor::ImgProcessor(QObject *parent) : QObject(parent)
{

}

ImgProcessor::ImgProcessor( ImgQueueSharedPointer_t que ) : mQueue(que)
{

}


void ImgProcessor::checkSize(){
    while(1){
        qDebug() << QThread::currentThreadId() << mQueue->size();
        QThread::msleep(mProcesTime);
    }
}

void ImgProcessor::ProcessTime( uint32_t time ){
    mProcesTime = time;
}
