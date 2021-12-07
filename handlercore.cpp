#include "handlercore.h"

#include <sstream>

using namespace bulk;

HandlerCore::HandlerCore(const size_t &bulkSize)
    : m_bulkSize(bulkSize)
{
    m_state = StateBasePtr{new StateStatic(HandlerCorePtr(this))};
}

void HandlerCore::registerLogger(logger::LogPtr logger)
{
    m_loggers.emplace_back(std::move(logger));
}

void HandlerCore::addCommand(const Cmd &cmd)
{
    m_state->processCommand(cmd);
}

void HandlerCore::addCommandEof()
{
    m_state->processEof();
}

void HandlerCore::setState(StateBasePtr state)
{
    m_state = std::move(state);
}

size_t HandlerCore::bulkSize() const
{
    return m_bulkSize;
}

size_t HandlerCore::cmdsSize() const
{
    return m_cmds.size();
}

size_t HandlerCore::bracketsSize() const
{
    return m_brackets.size();
}

void HandlerCore::pushOpenedBracket()
{
    m_brackets.push('{');
}

void HandlerCore::popOpenedBracket()
{
    m_brackets.pop();
}

void HandlerCore::pushCmd(const Cmd &cmd)
{
    m_cmds.push(cmd);
}

void HandlerCore::processBulk()
{
    std::ostringstream oss;
    std::ostream &os = oss;

    if (!m_cmds.empty()) {
        os << "bulk: ";
        while (!m_cmds.empty()) {
            os << m_cmds.front();
            m_cmds.pop();
            if (!m_cmds.empty()) {
                os << ", ";
            }
        }
        os << std::endl;
    }

    for (const auto &observer : m_loggers) {
        observer->write(oss.str());
        observer->close();
    }
}

void HandlerCore::closeLog()
{
    for (const auto &observer : m_loggers) {
        observer->close();
    }
}

void HandlerCore::openLog()
{
    for (const auto &observer : m_loggers) {
        observer->open();
    }
}

bool HandlerCore::isOpenedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, '{');
}

bool HandlerCore::isClosedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, '}');
}

bool HandlerCore::isAnyBracket(const Cmd &cmd, Bracket anyBracket)
{
    if (cmd.size() == 1) {
        return cmd.at(0) == anyBracket;
    } else {
        return false;
    }
}
