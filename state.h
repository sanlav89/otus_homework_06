#pragma once

#include "assignments.h"

namespace bulk {

class Handler;

class StateBase
{
public:
    StateBase(Handler *handler);
    virtual ~StateBase() = default;
    virtual void processCommand(const Cmd &cmd) = 0;
    virtual void processEof() = 0;

protected:
    Handler * m_handler;
};

class StateStatic : public StateBase
{
public:
    StateStatic(Handler *handler);
    void processCommand(const Cmd &cmd) override;
    void processEof() override;
};

class StateDynamic : public StateBase
{
public:
    StateDynamic(Handler *handler);
    void processCommand(const Cmd &cmd) override;
    void processEof() override;
};

using StateBasePtr = std::unique_ptr<StateBase>;

}

