#pragma once

#include <stack>
#include <queue>
#include <list>

#include "logger.h"
#include "assignments.h"
#include "state.h"

namespace bulk {

class HandlerCore
{
public:
    HandlerCore(const size_t &bulkSize);
    void registerLogger(logger::LogPtr logger);
    void addCommand(const Cmd &cmd);
    void addCommandEof();
    void setState(StateBasePtr state);
    size_t bulkSize() const;
    size_t cmdsSize() const;
    size_t bracketsSize() const;
    void pushOpenedBracket();
    void popOpenedBracket();
    void pushCmd(const Cmd &cmd);
    void processBulk();
    void openLog();
    void closeLog();

    static bool isOpenedBracket(const Cmd &cmd);
    static bool isClosedBracket(const Cmd &cmd);

private:
    size_t m_bulkSize;
    std::queue<Cmd> m_cmds;
    std::stack<Bracket> m_brackets;
    StateBasePtr m_state;
    std::list<logger::LogPtr> m_loggers;

    static bool isAnyBracket(const Cmd &cmd, Bracket anyBracket);

};

}

