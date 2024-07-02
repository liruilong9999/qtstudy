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
    return  true;
}

void PluginA::clean()
{

}

