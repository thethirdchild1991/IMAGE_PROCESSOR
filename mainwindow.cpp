#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QImageWriter>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->browseSRCPushButton,        &QPushButton::clicked, this, &MainWindow::browseSRCFolder);
    connect(ui->browseDSTPushButton,        &QPushButton::clicked, this, &MainWindow::browseDSTFolder);
    connect(ui->browseSingleImgPushButton,  &QPushButton::clicked, this, &MainWindow::browseSingleImg);
    connect(ui->startPushButton,            &QPushButton::clicked, this, &MainWindow::startBtnClicked);

    ui->srcFolderLineEdit->setText(
        mSettings.value(
                        Settings::settingsQStringNames(
                            Settings::settingsNames::SRCFolder
                            ),
                        QVariant(QString("")) ).toString()
    );

    ui->dstFolderLineEdit->setText(
        mSettings.value(
                        Settings::settingsQStringNames(
                            Settings::settingsNames::DSTFolder
                            ),
                        QVariant(QString("")) ).toString()
    );
    ui->singleImgLineEdit->setText(
        mSettings.value(
                        Settings::settingsQStringNames(
                            Settings::settingsNames::SingleImgPath
                            ),
                        QVariant(QString("")) ).toString()
    );

    ui->imgViewer->setScaledContents(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseSRCFolder(){
    ui->srcFolderLineEdit->setText( QFileDialog::getExistingDirectory() );
    mSettings.setValue(
        Settings::settingsQStringNames( Settings::settingsNames::SRCFolder ),
        ui->srcFolderLineEdit->text()
    );

}
void MainWindow::browseDSTFolder(){
    ui->dstFolderLineEdit->setText( QFileDialog::getExistingDirectory() );
    mSettings.setValue(
        Settings::settingsQStringNames( Settings::settingsNames::DSTFolder ),
        ui->dstFolderLineEdit->text()
    );
}

void MainWindow::browseSingleImg(){
    qDebug() << "Browse";
    ui->singleImgLineEdit->setText( QFileDialog::getOpenFileName() );
    mSettings.setValue(
        Settings::settingsQStringNames( Settings::settingsNames::SingleImgPath ),
        ui->singleImgLineEdit->text()
    );
}

void MainWindow::startBtnClicked(){
//    emit StartWorker( ui->srcFolderLineEdit->text() );
    emit StartSingleProcessor( ui->singleImgLineEdit->text() );
}


void MainWindow::setImg( ImageSharedPointer_t pImg ){
//    qDebug() << "NEW IMG : " << pImg->size();
    ui->imgViewer->setPixmap( QPixmap::fromImage( *pImg ) );

    QString srcFile = ui->singleImgLineEdit->text();
    qDebug() << QDir::separator();
    auto splited = srcFile.split( "/" );
    splited.pop_back();
    splited.push_back("processed.png");

    auto processedFilePath = splited.join( QDir::separator() );

    QImageWriter qimwr( processedFilePath );
    qimwr.write( *pImg );

//    ui->imgViewer->move(1,1);
}
