#ifndef LLOG_H
#define LLOG_H

#include <singleton/TSingleton.hpp>
#include <string>
#include "llog_global.h"


struct LLogPrivate;

class LLOG_EXPORT LLog : public TSingleton<LLog>
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
    void printWaringStd(std::string msg);
    void printWaring(QString msg);
    /*!
     * \brief printDebug 打印调试信息
     * \param msg
     */
    void printDebugStd(std::string msg);
    void printDebug(QString msg);

    /*!
     * \brief printError 打印错误信息
     * \param msg
     */
    void printErrorStd(std::string msg);
    void printError(QString msg);

    /*!
     * \brief printInfo 打印普通信息
     * \param msg
     */
    void printInfoStd(std::string msg);
    void printInfo(QString msg);

private:
    LLog();
    ~LLog();

private:
    LLogPrivate * m_logData = nullptr;
};

#define LOG_WARN(msg)  LLog::instance().printWaring(msg)
#define LOG_DEBUG(msg) LLog::instance().printDebug(msg)
#define LOG_INFO(msg)  LLog::instance().printInfo(msg)
#define LOG_ERROR(msg) LLog::instance().printError(msg)

#endif // LLOG_H
