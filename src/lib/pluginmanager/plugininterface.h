#ifndef PLUGININTERFACE__H__
#define PLUGININTERFACE__H__

#include <QString>
#include <QObject>

class PluginInterface
{
public:
    // 虚析构，保障内存上先释放子类
    virtual ~PluginInterface(){};

    virtual QString getname() = 0;
    virtual bool    init()    = 0;
    virtual bool    clean()   = 0;
};

#define PluginInterface_iid "lrl.QtPluginsManager.PluginInterFace"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif
