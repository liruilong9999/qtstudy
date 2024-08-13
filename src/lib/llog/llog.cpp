#include <string.h>
#include <iostream>
#include <QDateTime>
#include <QDebug>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "llog.h"

struct LLogPrivate
{
    bool                            isSave{true}; // 是否保存
    std::shared_ptr<spdlog::logger> mylogger;     // 日志保存到文件中
    //    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink ;//日志显示到控制台
};

void LLog::saveLog(bool isSave)
{
    if (m_logData)
    {
        m_logData->isSave = isSave;
    }
}

void LLog::printWaringStd(std::string msg)
{
    if (m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->warn(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printWaring(QString msg)
{
    qDebug() << "[Waring] " << msg;
    if (m_logData && m_logData->isSave)
        printWaringStd(msg.toStdString());
}

void LLog::printDebugStd(std::string msg)
{
    if (m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->debug(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printDebug(QString msg)
{
    qDebug() << "[Debug] " << msg;
    if (m_logData && m_logData->isSave)
        printDebugStd(msg.toStdString());
}

void LLog::printErrorStd(std::string msg)
{
    if (m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->error(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printError(QString msg)
{
    qDebug() << "[Error] " << msg;
    if (m_logData && m_logData->isSave)
        printErrorStd(msg.toStdString());
}

void LLog::printInfoStd(std::string msg)
{
    if (m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->info(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printInfo(QString msg)
{
    qDebug() << "[Info] " << msg;
    if (m_logData && m_logData->isSave)
        printInfoStd(msg.toStdString());
}

LLog::LLog()
{
    // 文件名（当前时间）
    QDateTime   curTime     = QDateTime::currentDateTime();
    QString     fileName    = curTime.toString("yyyy_MM_dd_hh_mm_ss");
    std::string logFileName = "./log/" + fileName.toStdString() + ".log";
    //    // 创建控制台 sink
    //    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    //    console_sink->set_level(spdlog::level::info);

    //    // 创建文件 sink
    //    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFileName, true);
    //    file_sink->set_level(spdlog::level::debug);

    m_logData           = new LLogPrivate;
    m_logData->mylogger = spdlog::basic_logger_mt("app", logFileName);
    m_logData->mylogger->set_pattern("[%n][%Y-%m-%d %H:%M:%S.%e] [%l] [%t]  %v");
    m_logData->mylogger->set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5)); // 定期刷新日志缓冲区

    //    // 创建多重日志记录器
    //    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    //    m_logData->mylogger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
    //    m_logData->mylogger->set_pattern("[%n][%Y-%m-%d %H:%M:%S.%e] [%l] [%t]  %v");
    //    m_logData->mylogger->set_level(spdlog::level::debug);

    //    // 设置全局日志器
    //    spdlog::set_default_logger(m_logData->mylogger);
    //    spdlog::flush_every(std::chrono::seconds(5)); // 定期刷新日志缓冲区
}

LLog::~LLog()
{
    if (m_logData)
    {
        delete m_logData;
        m_logData = nullptr;
    }
}
