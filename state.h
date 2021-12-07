#pragma once

#include "assignments.h"

namespace bulk {

class Handler;

using HandlerPtr = std::shared_ptr<Handler>;

class IState
{
public:
    virtual ~IState() = default;
    virtual void processCommand(const HandlerPtr &handler, const Cmd &cmd) = 0;
    virtual void processEof(const HandlerPtr &handler) = 0;
};


class StateStatic : public IState
{
public:
    StateStatic() = default;
    void processCommand(const HandlerPtr &handler, const Cmd &cmd) override;
    void processEof(const HandlerPtr &handler) override;
};

class StateDynamic : public IState
{
public:
    StateDynamic() = default;
    void processCommand(const HandlerPtr &handler, const Cmd &cmd) override;
    void processEof(const HandlerPtr &handler) override;
};

using StateBasePtr = std::unique_ptr<IState>;

}

