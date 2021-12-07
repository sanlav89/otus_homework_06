#include "handler.h"

#include <sstream>

using namespace bulk;

Handler::Handler(const size_t &bulkSize)
    : m_bulkSize(bulkSize)
    , m_state(StateBasePtr{new StateStatic})
{
}

void Handler::registerLog(log::LogPtr observer)
{
    m_observers.emplace_back(std::move(observer));
}

void Handler::addCommand(const Cmd &cmd)
{
    m_state->processCommand(this, cmd);
}

void Handler::addCommandEof()
{
    m_state->processEof(this);
}

void Handler::setState(StateBasePtr state)
{
    m_state = std::move(state);
}

size_t Handler::bulkSize() const
{
    return m_bulkSize;
}

size_t Handler::cmdsSize() const
{
    return m_cmds.size();
}

size_t Handler::bracketsSize() const
{
    return m_brackets.size();
}

void Handler::pushOpenedBracket()
{
    m_brackets.push('{');
}

void Handler::popOpenedBracket()
{
    m_brackets.pop();
}

void Handler::pushCmd(const Cmd &cmd)
{
    m_cmds.push(cmd);
}

void Handler::processBulk()
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

    for (const auto &observer : m_observers) {
        observer->write(oss.str());
        observer->close();
    }
}

void Handler::closeLog()
{
    for (const auto &observer : m_observers) {
        observer->close();
    }
}

void Handler::openLog()
{
    for (const auto &observer : m_observers) {
        observer->open();
    }
}

bool Handler::isOpenedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, '{');
}

bool Handler::isClosedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, '}');
}

bool Handler::isAnyBracket(const Cmd &cmd, Bracket anyBracket)
{
    if (cmd.size() == 1) {
        return cmd.at(0) == anyBracket;
    } else {
        return false;
    }
}
