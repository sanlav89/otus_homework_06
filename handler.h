#pragma once

#include "handlercore.h"

namespace bulk {

class Handler
{
public:
    Handler(const size_t &bulkSize);
    void registerLogger(logger::LogPtr logger);
    void addCommand(const Cmd &cmd);
    void addCommandEof();

private:
    HandlerCorePtr m_handlerCore;

};

}

