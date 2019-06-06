#include "mainwindow.h"
#include <QApplication>
#include "worker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Worker mworker(QString("D:/work/GSPV/DEBUG_IMAGES/all"));
//    mworker.start();

    MainWindow w;
    w.show();

    return a.exec();
}
