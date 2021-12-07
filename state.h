#pragma once

#include "assignments.h"

namespace bulk {

class Handler;

class IState
{
public:
    virtual ~IState() = default;
    virtual void processCommand(Handler *handler, const Cmd &cmd) = 0;
    virtual void processEof(Handler *handler) = 0;
};


class StateStatic : public IState
{
public:
    StateStatic() = default;
    void processCommand(Handler *handler, const Cmd &cmd) override;
    void processEof(Handler *handler) override;
};

class StateDynamic : public IState
{
public:
    StateDynamic() = default;
    void processCommand(Handler *handler, const Cmd &cmd) override;
    void processEof(Handler *handler) override;
};

using StateBasePtr = std::unique_ptr<IState>;

}

