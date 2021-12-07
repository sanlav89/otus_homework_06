#include "log.h"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace log;

void Console::open()
{
    // ignore
}

void Console::close()
{
    // ignore
}

void Console::write(const std::string &log)
{
    std::cout << log;
}

void LogFile::open()
{
    auto result = std::time(nullptr);
    std::ostringstream oss;
    std::ostream &os = oss;
    os << "bulk" << result << ".log";
    m_logFile.open(oss.str());
}

void LogFile::close()
{
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void LogFile::write(const std::string &log)
{
    if (m_logFile.is_open()) {
        m_logFile << log;
    }
}
