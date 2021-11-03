#include "mainwindow.h"
#include "updategui.h"
#include <QApplication>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    UpdateGui GUI;
//    GUI.start();
//    updateGuistart();

    return a.exec();
}
