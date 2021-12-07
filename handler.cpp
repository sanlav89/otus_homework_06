#include "handler.h"

using namespace bulk;

Handler::Handler(const size_t &bulkSize)
{
    m_handlerCore = HandlerCorePtr{new HandlerCore(bulkSize)};
}

void Handler::registerLogger(logger::LogPtr logger)
{
    m_handlerCore->registerLogger(std::move(logger));
}

void Handler::addCommand(const Cmd &cmd)
{
    m_handlerCore->addCommand(cmd);
}

void Handler::addCommandEof()
{
    m_handlerCore->addCommandEof();
}
