#pragma once

#include <stack>
#include <queue>
#include <list>

#include "log.h"
#include "assignments.h"
#include "state.h"

namespace bulk {

class Handler : public std::enable_shared_from_this<Handler>
{
public:
    Handler(const size_t &bulkSize);
    void registerLog(log::LogPtr obs);

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
    std::list<log::LogPtr> m_observers;

    static bool isAnyBracket(const Cmd &cmd, Bracket anyBracket);

};

}

