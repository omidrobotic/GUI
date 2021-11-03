#include "updategui.h"
#include "sql.h"

UpdateGui::UpdateGui(QObject *parent):
    QThread(parent)
{

}
void UpdateGui::run()
{
    std::cout<<"hello";
    for (int i = 0; i < 10000; ++i) {
        QMutex mutex;
        mutex.lock();
        if(this->stop) break;
        mutex.unlock();

        emit nextUpdate();
    }
}
