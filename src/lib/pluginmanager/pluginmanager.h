#ifndef PLUGINMANAGER_H__
#define PLUGINMANAGER_H__
#include <QPluginLoader>
#include "pluginmanager_gloabal.h"

class PluginManagerPrivate;
class QString;
class PLUGINSMANAGERSHARED_EXPORT PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager& GetInstance();
    /*!
     * \brief loadPlugin 加载指定插件
     * \param filePath 插件的路径
     * \return
     */
    bool loadPlugin(QString & filePath);

    /*!
     * \brief unloadPlugin 卸载指定的插件
     * \param filePath 插件的路径
     * \return
     */
    bool unloadPlugin(QString & filePath);

    /*!
     * \brief loadAllPlugin 加载所有插件
     * \return
     */
    bool loadAllPlugin();

    /*!
     * \brief unloadAllPlugin 卸载所有插件
     * \return
     */
    bool unloadAllPlugin();

    /*!
     * \brief getPluginsName 获取已加载插件的名称
     * \return
     */
    QList<QString> getPluginsName();

    /*!
     * \brief scanMetaData 初始化元数据
     * \param filepath
     */
    void scanMetaData(const QString &filepath);

    void setPluginList();

private:
    PluginManager();
    ~PluginManager();

private:
    QString m_configFile;
    PluginManagerPrivate * m_pluginData = nullptr;
};

#endif
