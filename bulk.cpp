#include "bulk.h"

#include <iostream>

using namespace bulk;

BulkHandler::BulkHandler(const size_t &bulkSize)
    : m_bulkSize(bulkSize)
    , m_state(BulkHandlerBasePtr{new StateStatic(this)})
{
}

void BulkHandler::addCommand(const Cmd &cmd)
{
    m_state->processCommand(cmd);
}

void BulkHandler::addCommandEof()
{
    m_state->processEof();
}

void BulkHandler::setState(BulkHandlerBasePtr state)
{
    m_state = std::move(state);
}

size_t BulkHandler::bulkSize() const
{
    return m_bulkSize;
}

size_t BulkHandler::cmdsSize() const
{
    return m_cmds.size();
}

size_t BulkHandler::bracketsSize() const
{
    return m_brackets.size();
}

void BulkHandler::pushOpenedBracket()
{
    m_brackets.push(openedBracket());
}

void BulkHandler::popOpenedBracket()
{
    m_brackets.pop();
}

void BulkHandler::addCmdToQueue(const Cmd &cmd)
{
    m_cmds.push(cmd);
}

void BulkHandler::processBulk()
{
    if (!m_cmds.empty()) {
        std::cout << "bulk: ";
        while (!m_cmds.empty()) {
            std::cout << m_cmds.front();
            m_cmds.pop();
            if (!m_cmds.empty()) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

bool BulkHandler::isOpenedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, openedBracket());
}

bool BulkHandler::isClosedBracket(const Cmd &cmd)
{
    return isAnyBracket(cmd, closedBracket());
}

bool BulkHandler::isAnyBracket(const Cmd &cmd, Bracket anyBracket)
{
    if (cmd.size() == 1) {
        return cmd.at(0) == anyBracket;
    } else {
        return false;
    }
}

StateStatic::StateStatic(BulkHandler *handler) : BulkHandlerBase(handler)
{
}

void StateStatic::processCommand(const Cmd &cmd)
{
    if (BulkHandler::isOpenedBracket(cmd)) {
        m_handler->pushOpenedBracket();
        m_handler->processBulk();
        m_handler->setState(BulkHandlerBasePtr{new StateDynamic(m_handler)});
    } else {
        m_handler->addCmdToQueue(cmd);
        if (m_handler->cmdsSize() == m_handler->bulkSize()) {
            m_handler->processBulk();
        }
    }
}

void StateStatic::processEof()
{
    m_handler->processBulk();
}

StateDynamic::StateDynamic(BulkHandler *handler) : BulkHandlerBase(handler)
{
}

void StateDynamic::processCommand(const Cmd &cmd)
{
    if (BulkHandler::isClosedBracket(cmd)) {
        m_handler->popOpenedBracket();
        if (m_handler->bracketsSize() == 0) {
            m_handler->processBulk();
            m_handler->setState(BulkHandlerBasePtr{new StateStatic(m_handler)});
        }
    } else if (BulkHandler::isOpenedBracket(cmd)) {
        m_handler->pushOpenedBracket();
    } else {
        m_handler->addCmdToQueue(cmd);
    }
}

void StateDynamic::processEof()
{
    // ignore
}
