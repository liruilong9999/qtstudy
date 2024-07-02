#include <string.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "llog.h"

struct LLogPrivate
{
    bool isSave {true}; //是否保存
    std::shared_ptr<spdlog::logger> mylogger;
};

void LLog::saveLog(bool isSave)
{
    if(m_logData)
    {
        m_logData->isSave = isSave;
    }
}

void LLog::printWaring(std::string msg)
{
    if(m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->warn(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printDebug(std::string msg)
{
    if(m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->debug(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printError(std::string msg)
{
    if(m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->error(msg);
        m_logData->mylogger->flush();
    }
}

void LLog::printInfo(std::string msg)
{
    if(m_logData && m_logData->mylogger)
    {
        m_logData->mylogger->info(msg);
        m_logData->mylogger->flush();
    }
}

LLog::LLog()
{
    m_logData = new LLogPrivate;
    m_logData->mylogger = spdlog::basic_logger_mt("spdlog", "spdlog.log");
    m_logData->mylogger->set_pattern("[%n][%Y-%m-%d %H:%M:%S.%e] [%l] [%t]  %v");
    m_logData->mylogger->set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5)); // 定期刷新日志缓冲区
}

LLog::~LLog()
{
    if(m_logData)
    {
        delete m_logData;
        m_logData = nullptr;
    }
}
