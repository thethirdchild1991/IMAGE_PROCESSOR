#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include "ImgReader.h"
#include "imgprocessor.h"
#include "worker.h"
#include "cogprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType< ImageSharedPointer_t >();

    ImgQueueSharedPointer_t mQueue = std::make_shared<ImgQueue_t>();



    QThread* thread = new QThread;
    Worker* mWorker = new Worker();
    CogProcessor* mCogProcessor = new CogProcessor();


    MainWindow w;

    QList<QThread*> threadList;

    mWorker->moveToThread(thread);

    QThread* imgReaderThread = new QThread;
    ImgReader* mImgReader = new ImgReader(mQueue);
    mImgReader->moveToThread(imgReaderThread);
    QObject::connect( &w, &MainWindow::StartWorker, mWorker, &Worker::doWork );
    QObject::connect( &w, &MainWindow::StartSingleProcessor, mCogProcessor, &CogProcessor::process );
    QObject::connect( mWorker, &Worker::newImage, &w, &MainWindow::setImg );
    QObject::connect( mCogProcessor, &CogProcessor::ready, &w, &MainWindow::setImg );

    QObject::connect( &w, &MainWindow::StartWorker, mImgReader, &ImgReader::doWork );
    QObject::connect( mImgReader, &ImgReader::newImage, &w, &MainWindow::setImg );

    threadList.push_back(imgReaderThread);

    for(auto i = 0; i < 2; i++){
        auto tmpThread = new QThread;
        auto tmpImgProcessor = new ImgProcessor(mQueue);
        tmpImgProcessor->ProcessTime(50*i);
        tmpImgProcessor->moveToThread(tmpThread);

        QObject::connect( &w, &MainWindow::StartWorker, tmpImgProcessor, &ImgProcessor::checkSize );

        threadList.push_back(tmpThread);
    }


    for(auto thread : threadList){
        thread->start();
    }

//    thread->start();
    w.show();


    return a.exec();
}
