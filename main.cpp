#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include "worker.h"
#include "cogprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType< ImageSharedPointer_t >();


    QThread* thread = new QThread;
    Worker* mWorker = new Worker();
    CogProcessor* mCogProcessor = new CogProcessor();


    MainWindow w;


    mWorker->moveToThread(thread);

    QObject::connect( &w, &MainWindow::StartWorker, mWorker, &Worker::doWork );
    QObject::connect( &w, &MainWindow::StartSingleProcessor, mCogProcessor, &CogProcessor::process );
    QObject::connect( mWorker, &Worker::newImage, &w, &MainWindow::setImg );
    QObject::connect( mCogProcessor, &CogProcessor::ready, &w, &MainWindow::setImg );

//    thread->start();
    w.show();

    return a.exec();
}
