#include "state.h"
#include "handler.h"

using namespace bulk;

StateBase::StateBase(const HandlerPtr &handler) : m_handler(handler)
{
}

StateStatic::StateStatic(const HandlerPtr &handler) : StateBase(handler)
{
}

void StateStatic::processCommand(const Cmd &cmd)
{
    if (m_handler->cmdsSize() == 0) {
        m_handler->openLog();
    }
    if (Handler::isOpenedBracket(cmd)) {
        m_handler->pushOpenedBracket();
        m_handler->processBulk();
        m_handler->setState(StateBasePtr{new StateDynamic(m_handler)});
    } else {
        m_handler->pushCmd(cmd);
        if (m_handler->cmdsSize() == m_handler->bulkSize()) {
            m_handler->processBulk();
        }
    }
}

void StateStatic::processEof()
{
    m_handler->processBulk();
}

StateDynamic::StateDynamic(const HandlerPtr &handler) : StateBase(handler)
{
}

void StateDynamic::processCommand(const Cmd &cmd)
{
    if (m_handler->cmdsSize() == 0) {
        m_handler->openLog();
    }
    if (Handler::isClosedBracket(cmd)) {
        m_handler->popOpenedBracket();
        if (m_handler->bracketsSize() == 0) {
            m_handler->processBulk();
            m_handler->setState(StateBasePtr{new StateStatic(m_handler)});
        }
    } else if (Handler::isOpenedBracket(cmd)) {
        m_handler->pushOpenedBracket();
    } else {
        m_handler->pushCmd(cmd);
    }
}

void StateDynamic::processEof()
{
    m_handler->closeLog();
}
