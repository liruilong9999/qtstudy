
#ifndef PLUGINB_H
#define PLUGINB_H

#include <QObject>
#include <QtPlugin>
#include <pluginmanager/plugininterface.h>

class PluginB : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pluginb" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginB(QObject *parent = 0);
    virtual QString getname() override;
    virtual bool init()override;
    virtual void clean()override;
};
#endif // PLUGINB_H
