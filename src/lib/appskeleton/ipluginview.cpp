
#include <QDebug>
#include "ipluginview.h"
// 获取 IPluginView 实例

QMutex IPluginView::m_mutex;

IPluginView & IPluginView::getInstance()
{
    QMutexLocker locker(&m_mutex);

    static IPluginView instance;
    return instance;
}

// 注册组
void IPluginView::registerGroup(const QString & groupName)
{
    if (!m_groups.contains(groupName))
    {
        m_groups[groupName] = {groupName, {}};
        // qDebug() << "Group registered:" << groupName;
    }
}

// 注册页
void IPluginView::registerPage(const QString & groupName, const QString & pageName)
{
    registerGroup(groupName); // 确保组存在
    if (!m_groups[groupName].pages.contains(pageName))
    {
        m_groups[groupName].pages[pageName] = {pageName, {}};
        // qDebug() << "Page registered in group" << groupName << ":" << pageName;
    }
}

// 注册动作
void IPluginView::registerAction(const QString & groupName, const QString & pageName, QAction * action)
{
    registerPage(groupName, pageName); // 确保页存在
    if (!m_groups[groupName].pages[pageName].actions.contains(action->text()))
    {
        m_groups[groupName].pages[pageName].actions[action->text()] = {action->text(), action};
        // qDebug() << "Action registered in page" << pageName << "of group" << groupName << ":" << action->text();
    }
}

// 获取主窗口
AppSkeleton * IPluginView::getMainWindow() const
{
    return m_mainWindow;
}

// 创建菜单栏
void IPluginView::createMenuBar(QMenuBar * menuBar)
{
    for (const auto & group : m_groups)
    {
        QMenu * menu = menuBar->addMenu(group.name);
        for (const auto & page : group.pages)
        {
            QMenu * subMenu = menu->addMenu(page.name);
            for (const auto & action : page.actions)
            {
                subMenu->addAction(action.actionPtr);
            }
        }
    }
}

IPluginView::IPluginView()
{
    m_mainWindow = new AppSkeleton;
}
