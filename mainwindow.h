#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDir>
#include "worker.h"

namespace Ui {
class MainWindow;
}

namespace Settings {
enum class settingsNames{
    SRCFolder,
    DSTFolder
};

static QString settingsQStringNames( const settingsNames name ){
    const QMap<settingsNames, QString> map = {
        {settingsNames::SRCFolder, QString("SRCFolder") },
        {settingsNames::DSTFolder, QString("DSTFolder") },
    };
    return map.value(name);
}
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    signals:
    void StartWorker( QString );

    public slots:
    void browseSRCFolder();
    void browseDSTFolder();
    void startBtnClicked();
    void setImg( ImageSharedPointer_t pImg );

private:
    Ui::MainWindow *ui;
    Worker* mWorker;
    QSettings mSettings = { "settings.ini", QSettings::Format::IniFormat };
};

#endif // MAINWINDOW_H
