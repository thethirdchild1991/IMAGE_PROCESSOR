#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>

#include "worker.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->browseSRCPushButton,    &QPushButton::clicked, this, &MainWindow::browseSRCFolder);
    connect(ui->browseDSTPushButton,    &QPushButton::clicked, this, &MainWindow::browseDSTFolder);
    connect(ui->startPushButton,        &QPushButton::clicked, this, &MainWindow::startBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseSRCFolder(){
    ui->srcFolderLineEdit->setText( QFileDialog::getExistingDirectory() );

}
void MainWindow::browseDSTFolder(){
    ui->dstFolderLineEdit->setText( QFileDialog::getExistingDirectory() );

}

void MainWindow::startBtnClicked(){
    auto pathString = ui->srcFolderLineEdit->text();

//    QDir srcDir(pathString);
//    srcDir.setFilter( QDir::Files );
//    srcDir.setSorting( QDir::Name );

//    auto filenamesList = srcDir.entryList();


//    for( auto filename : filenamesList){
//        qDebug() << filename;
//    }
    mWorker = new Worker(pathString);
    mWorker->start();

}
