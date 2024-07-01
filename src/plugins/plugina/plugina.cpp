#include <QDebug>
#include "plugina.h"

PluginA::PluginA(QObject *parent) :
    QObject(parent)
{
}

QString PluginA::getname()
{
    return QStringLiteral("插件A");
}

bool PluginA::init()
{
    qDebug() << QStringLiteral("插件A加载成功");
    return  true;
}

void PluginA::clean()
{
    qDebug() <<  QStringLiteral("插件A卸载成功");
}

