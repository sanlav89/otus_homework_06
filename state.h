#pragma once

#include "assignments.h"

namespace bulk {

class StateBase
{
public:
    StateBase(const HandlerCorePtr &handler);
    virtual ~StateBase() = default;
    virtual void processCommand(const Cmd &cmd) = 0;
    virtual void processEof() = 0;

protected:
    HandlerCorePtr m_handler;
};

class StateStatic : public StateBase
{
public:
    StateStatic(const HandlerCorePtr &handler);
    void processCommand(const Cmd &cmd) override;
    void processEof() override;
};

class StateDynamic : public StateBase
{
public:
    StateDynamic(const HandlerCorePtr &handler);
    void processCommand(const Cmd &cmd) override;
    void processEof() override;
};

using StateBasePtr = std::unique_ptr<StateBase>;

}

