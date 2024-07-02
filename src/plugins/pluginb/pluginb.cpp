#include <QDebug>
#include "pluginb.h"

PluginB::PluginB(QObject *parent) :
    QObject(parent)
{
}

QString PluginB::getname()
{
    return QStringLiteral("插件B");
}

bool PluginB::init()
{
    return  true;
}

void PluginB::clean()
{
}

