#pragma once

#include <stack>
#include <queue>
#include <string>
#include <memory>

namespace bulk {

using Cmd = std::string;
using Bracket = char;

class BulkHandler;

class BulkHandlerBase
{
public:
    BulkHandlerBase(BulkHandler *handler) : m_handler(handler) {}
    virtual ~BulkHandlerBase() = default;
    virtual void processCommand(const Cmd &cmd) = 0;

protected:
    BulkHandler *m_handler;
};

using BulkHandlerBasePtr =  std::unique_ptr<BulkHandlerBase>;

class BulkHandler
{
public:
    BulkHandler(const size_t &bulkSize);
    void addCommand(const Cmd &cmd);
    void setState(BulkHandlerBasePtr state);
    size_t bulkSize() const;
    size_t cmdsSize() const;
    size_t bracketsSize() const;

    void pushOpenedBracket();
    void popOpenedBracket();
    void addCmdToQueue(const Cmd &cmd);
    void processBulk();

    static Bracket openedBracket() { return '{'; }
    static Bracket closedBracket() { return '}'; }
    static bool isOpenedBracket(const Cmd &cmd);
    static bool isClosedBracket(const Cmd &cmd);

private:
    size_t m_bulkSize;
    std::queue<Cmd> m_cmds;
    std::stack<Bracket> m_brackets;
    BulkHandlerBasePtr m_state;

    static bool isAnyBracket(const Cmd &cmd, Bracket anyBracket);


};

class StateStatic : public BulkHandlerBase
{
public:
    StateStatic(BulkHandler *handler); //  : BulkHandlerBase(handler) {}
    void processCommand(const Cmd &cmd) override;
};

class StateDynamic : public BulkHandlerBase
{
public:
    StateDynamic(BulkHandler *handler); // : BulkHandlerBase(handler) {}
    void processCommand(const Cmd &cmd) override;
};

}

