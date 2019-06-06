#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    public slots:
    void browseSRCFolder();
    void browseDSTFolder();
    void startBtnClicked();


private:
    Ui::MainWindow *ui;
    Worker* mWorker;
};

#endif // MAINWINDOW_H
