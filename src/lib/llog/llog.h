#ifndef LLOG_H
#define LLOG_H

#include <singleton/TSingleton.hpp>
#include <string>
#include "llog_global.h"


struct LLogPrivate;

class LLOG_EXPORT LLog : TSingleton<LLog>
{
    friend class TSingleton<LLog>;
public:
    /*!
     * \brief saveLog 是否保存log到本地
     * \param isSave 默认保存
     */
    void saveLog(bool isSave = true);

    /*!
     * \brief printWaring 打印警告信息
     * \param msg
     */
    void printWaring(std::string msg);

    /*!
     * \brief printDebug 打印调试信息
     * \param msg
     */
    void printDebug(std::string msg);

    /*!
     * \brief printError 打印错误信息
     * \param msg
     */
    void printError(std::string msg);

    /*!
     * \brief printInfo 打印普通信息
     * \param msg
     */
    void printInfo(std::string msg);

private:
    LLog();
    ~LLog();

private:
    LLogPrivate * m_logData = nullptr;
};

//LLog::instance();

#define LOG_WARN(msg)

#endif // LLOG_H
