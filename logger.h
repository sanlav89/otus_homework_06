#pragma once

#include <fstream>
#include <memory>

namespace logger {

class ILogger
{
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void write(const std::string &log) = 0;
};

class Console : public ILogger
{
public:
    Console() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;
};

class LogFile : public ILogger
{
public:
    LogFile() = default;
    void open() override;
    void close() override;
    void write(const std::string &log) override;

private:
    std::ofstream m_logFile;
    std::string m_logFileName;
};

using LogPtr = std::unique_ptr<ILogger>;

}

