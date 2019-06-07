#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include "worker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType< ImageSharedPointer_t >();


    QThread* thread = new QThread;
    Worker* mWorker = new Worker();
    MainWindow w;

    mWorker->moveToThread(thread);

    QObject::connect( &w, &MainWindow::StartWorker, mWorker, &Worker::doWork );
    QObject::connect( mWorker, &Worker::newImage, &w, &MainWindow::setImg );

    thread->start();
    w.show();

    return a.exec();
}
