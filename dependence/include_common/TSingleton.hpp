#ifndef TSINGLETON_H
#define TSINGLETON_H

#include <QMutex>
#include <QMutexLocker>

template <class T>
class TSingleton
{
public:
    // 获取单例实例
    static T * getInstance();

    static QMutex m_mutex; // 保护实例的互斥量

protected:
    TSingleton()  = default;
    ~TSingleton() = default;

    // 删除拷贝构造函数，赋值运算符，移动构造函数，移动赋值运算符，防止复制实例
    TSingleton(const TSingleton &)             = delete;
    TSingleton & operator=(const TSingleton &) = delete;
    TSingleton(TSingleton &&)                  = delete;
    TSingleton & operator=(TSingleton &&)      = delete;
};

template <class T>
QMutex TSingleton<T>::m_mutex;

template <class T>
T * TSingleton<T>::getInstance()
{
    QMutexLocker locker(&m_mutex);
    static T     instance;
    return &instance;
}

#endif // TSINGLETON_H
