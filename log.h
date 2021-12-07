#pragma once

#include <fstream>
#include <memory>

namespace log {

class Log
{
public:
    virtual ~Log() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void write(const std::string &log) = 0;
};

class Console : public Log
{
public:
    Console() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;
};

class LogFile : public Log
{
public:
    LogFile() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;

private:
    std::ofstream m_logFile;
};

using LogPtr = std::unique_ptr<Log>;

}

