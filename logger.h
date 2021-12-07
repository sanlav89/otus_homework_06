#pragma once

#include <fstream>
#include <memory>

namespace logger {

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void write(const std::string &log) = 0;
};

class Console : public Logger
{
public:
    Console() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;
};

class LogFile : public Logger
{
public:
    LogFile() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;

private:
    std::ofstream m_logFile;
};

using LogPtr = std::unique_ptr<Logger>;

}

