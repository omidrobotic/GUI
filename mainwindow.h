#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "updategui.h"


#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    UpdateGui *Gui;
    QTimer *timer;

public slots:
    void nextUpdateGUI();

private slots:
    void on_configPushButton_clicked();
    void on_configAdd_clicked();


    void on_saveButton_clicked();

    void on_refreshButton_clicked();

    void on_configRemove_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
