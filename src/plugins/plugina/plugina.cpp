#include <QDebug>
#include <lib/appskeleton/ipluginview.h>
#include <QAction>
#include <QLabel>
#include <QStatusBar>

#include <lib/leventbus/leventbus.h>
#include <lib/llog/llog.h>

#include <include_common/CircularQueue.h>

#include "plugina.h"
#include "testclass.h"

PluginA::PluginA(QObject * parent)
    : QObject(parent)
{
}

QString PluginA::getname()
{
    return QStringLiteral("插件A");
}

bool PluginA::init()
{
    m_TestClass       = new TestClass;
    m_actionTestClass = new QAction(QStringLiteral("按钮1"));
    if (m_actionTestClass)
    {
        connect(m_actionTestClass, &QAction::triggered, this, &PluginA::addTestClass);
        IPluginView::getInstance().registerAction(QStringLiteral("组"), QStringLiteral("页"), m_actionTestClass);
    }
    return true;
}

bool PluginA::clean()
{
    return true;
}

void PluginA::addTestClass()
{
    if (m_TestClass)
    {
    }
}
