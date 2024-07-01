
#ifndef PLUGINA_H
#define PLUGINA_H

#include <QObject>
#include <QtPlugin>
#include <pluginmanager/plugininterface.h>
#include "plugina_global.h"

class PLUGINA_EXPORT PluginA : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(InterfacePlugin)
public:
    explicit PluginA(QObject *parent = 0);
    virtual QString getname() override;
    virtual bool init()override;
    virtual void clean()override;
};
#endif // PLUGINA_H
