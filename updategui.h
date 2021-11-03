#ifndef UPDATEGUI_H
#define UPDATEGUI_H
#include <QtCore>
#include <qthread.h>

class UpdateGui : public QThread
{
    Q_OBJECT
public:
    explicit UpdateGui(QObject *parent=0);
    UpdateGui();
    void run();
    bool stop;

signals:
    void nextUpdate();
};

#endif // UPDATEGUI_H
