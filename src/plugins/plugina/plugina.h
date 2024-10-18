
#ifndef PLUGINA_H
#define PLUGINA_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class TestClass;
class PluginA : public QObject,
                public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PluginA" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginA(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addTestClass();

private:
    QAction *   m_actionTestClass{nullptr}; // 按钮
    TestClass * m_TestClass{nullptr};       // 类
};

#endif
