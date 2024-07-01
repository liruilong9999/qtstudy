#include <QString>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QFileInfoList>
#include "pluginmanager.h"
#include "plugininterface.h"

#define PLUGIN_CONF_PATH QString(qApp->applicationDirPath() + "/config/plugins.json");

struct PluginCongInfo
{
    QString pluginName{""};
    QString isUsed {"1"};
};

/*!
 * \brief The PluginManagerPrivate class 对已加载的所有插件进行维护
 */
class PluginManagerPrivate
{
public:
    //插件依赖检测
    bool check(const QString &filepath);

    QHash<QString, QVariant> m_names; //插件路径--插件名称
    QHash<QString, QVariant> m_versions; //插件路径--插件版本
    QHash<QString, QVariantList>m_dependencies; //插件路径--插件额外依赖的其他插件
    QHash<QString, QPluginLoader *>m_loaders; //插件路径--QPluginLoader实例
    QHash<QString, PluginCongInfo> pluginCongInfo;
};

bool PluginManagerPrivate::check(const QString &filepath)
{
    for(QVariant item : m_dependencies.value(filepath))
    {
        QVariantMap map = item.toMap();
        //依赖的插件名称、版本、路径
        QVariant name = map.value("name");
        QVariant version = map.value("version");
        QString path = m_names.key(name);

        /********** 检测插件是否依赖于其他插件 **********/
        // 先检测插件名称
        if(!m_names.values().contains(name))
        {
            QString strcons = "Missing dependency: "+ name.toString()+" for plugin "+path;
            qDebug()<<Q_FUNC_INFO<<strcons;
            //QMessageBox::warning(nullptr, ("Plugins Loader Error"), strcons, QMessageBox::Ok);
            return false;
        }
        //再检测插件版本
        if(m_versions.value(path) != version)
        {
            QString strcons = "Version mismatch: " + name.toString() +" version "+m_versions.value(m_names.key(name)).toString()+
                    " but " + version.toString() + " required for plugin "+path;
            qDebug()<<Q_FUNC_INFO<<strcons;
            //QMessageBox::warning(nullptr, "Plugins Loader Error", strcons, QMessageBox::Ok);
            return false;
        }
        //最后检测被依赖的插件是否还依赖其他的插件
        if(!check(path))
        {
            QString strcons = "Corrupted dependency: "+name.toString()+" for plugin "+path;
            qDebug()<<Q_FUNC_INFO<<strcons;
            //QMessageBox::warning(nullptr, "Plugins Loader Error", strcons, QMessageBox::Ok);
            return false;
        }
    }

    return true;
}

PluginManager &PluginManager::GetInstance()
{
    static PluginManager instance;
    return instance;
}

bool PluginManager::loadPlugin(QString &filePath)
{
    if(!QLibrary::isLibrary(filePath))
        return false;

    //检测依赖
    if(!m_pluginData && !m_pluginData->check(filePath))
        return false;

    //加载插件
    QPluginLoader *loader = new QPluginLoader(filePath);
    if(loader->load())
    {
        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
        PluginInterface *plugin = qobject_cast<PluginInterface *>(loader->instance());
        if(plugin)
        {
            m_pluginData->m_loaders.insert(filePath, loader);
        }
        else
        {
            delete loader;
            loader = nullptr;
        }
        return true;
    }
    return false;
}

bool PluginManager::unloadPlugin(QString &filePath)
{
    if(!m_pluginData)
        return false;
    QPluginLoader *loader = m_pluginData->m_loaders.value(filePath);
    //卸载插件，并从内部数据结构中移除
    if(loader && loader->unload())
    {
        m_pluginData->m_loaders.remove(filePath);
        delete loader;
        loader = nullptr;
        return  true;
    }
    return false;
}

bool PluginManager::loadAllPlugin()
{
    //获取插件配置文件
    setPluginList();

    QDir pluginsdir = QDir(qApp->applicationDirPath());
    pluginsdir.cd("plugins");
    QFileInfoList pluginsInfo = pluginsdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList useableList;

    for (const QFileInfo fileInfo : pluginsInfo)
    {
        if (QLibrary::isLibrary(fileInfo.absoluteFilePath()))
        {
            QString fileName = fileInfo.baseName(); // 获取插件文件的基本名（不含路径和扩展名）
            if (m_pluginData->pluginCongInfo.contains(fileName))
            {
                PluginCongInfo config = m_pluginData->pluginCongInfo.value(fileName);
                if (config.isUsed == "1")
                {
                    useableList.push_back(fileInfo);
                }
            }
        }
    }

    //初始化插件中的元数据
    for(QFileInfo fileinfo : useableList)
        scanMetaData(fileinfo.absoluteFilePath());

    //加载插件
    for(QFileInfo fileinfo : useableList)
    {
        QString path = fileinfo.absoluteFilePath();
        loadPlugin(path);
    }
    return true;
}

bool PluginManager::unloadAllPlugin()
{
    if(!m_pluginData)
        return false;
    foreach (auto filepath, m_pluginData->m_loaders.keys())
    {
        unloadPlugin(filepath);
    }
    return true;
}

QList<QString> PluginManager::getPluginsName()
{
    QList<QString> res;
    return res;
}

void PluginManager::scanMetaData(const QString &filepath)
{
    if(!m_pluginData)
        return;
    //判断是否为库（后缀有效性）
    if(!QLibrary::isLibrary(filepath))
        return ;
    //获取元数据
    QPluginLoader *loader = new QPluginLoader(filepath);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    QVariant var = json.value("name").toVariant();
    m_pluginData->m_names.insert(filepath, json.value("name").toVariant());
    m_pluginData->m_versions.insert(filepath, json.value("version").toVariant());
    m_pluginData->m_dependencies.insert(filepath, json.value("dependencies").toArray().toVariantList());

    delete loader;
    loader = nullptr;
}

void PluginManager::setPluginList()
{
    m_configFile = PLUGIN_CONF_PATH;

    QFile file(m_configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open config file:" << m_configFile;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QJsonArray pluginArray = obj["plugins"].toArray();

    m_pluginData->pluginCongInfo.clear();
    foreach (const QJsonValue &value, pluginArray)
    {
        QJsonObject pluginObj = value.toObject();
        QString pluginName = pluginObj["name"].toString();
        bool isUsed = pluginObj["isUsed"].toBool();
        PluginCongInfo info;
        info.pluginName = pluginName;
        info.isUsed = isUsed;

        m_pluginData->pluginCongInfo.insert(info.pluginName,info);
    }

}

PluginManager::PluginManager()
{
    m_pluginData = new PluginManagerPrivate;
}

PluginManager::~PluginManager()
{
    if(m_pluginData)
    {
        delete m_pluginData;
        m_pluginData = nullptr;
    }
}

