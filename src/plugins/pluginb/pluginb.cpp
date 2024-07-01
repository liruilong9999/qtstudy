#include <QDebug>
#include "pluginb.h"

PluginB::PluginB(QObject *parent) :
    QObject(parent)
{
}

QString PluginB::getname()
{
    return QStringLiteral("插件A");
}

bool PluginB::init()
{
    qDebug() << QStringLiteral("插件A加载成功");
    return  true;
}

void PluginB::clean()
{
    qDebug() <<  QStringLiteral("插件A卸载成功");
}

