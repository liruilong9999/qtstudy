#include <QApplication>
#include <pluginmanager/pluginmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PluginManager::GetInstance().loadAllPlugin();
    int ret = a.exec();
    PluginManager::GetInstance().unloadAllPlugin();

    return ret;
}
