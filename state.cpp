#include "state.h"
#include "handlercore.h"

using namespace bulk;

StateBase::StateBase(const HandlerCorePtr &handler) : m_handler(handler)
{
}

StateStatic::StateStatic(const HandlerCorePtr &handler) : StateBase(handler)
{
}

void StateStatic::processCommand(const Cmd &cmd)
{
    if (m_handler->cmdsSize() == 0) {
        m_handler->openLog();
    }
    if (HandlerCore::isOpenedBracket(cmd)) {
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

StateDynamic::StateDynamic(const HandlerCorePtr &handler) : StateBase(handler)
{
}

void StateDynamic::processCommand(const Cmd &cmd)
{
    if (m_handler->cmdsSize() == 0) {
        m_handler->openLog();
    }
    if (HandlerCore::isClosedBracket(cmd)) {
        m_handler->popOpenedBracket();
        if (m_handler->bracketsSize() == 0) {
            m_handler->processBulk();
            m_handler->setState(StateBasePtr{new StateStatic(m_handler)});
        }
    } else if (HandlerCore::isOpenedBracket(cmd)) {
        m_handler->pushOpenedBracket();
    } else {
        m_handler->pushCmd(cmd);
    }
}

void StateDynamic::processEof()
{
    m_handler->closeLog();
}
