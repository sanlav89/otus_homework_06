#include "state.h"
#include "handler.h"

using namespace bulk;

void StateStatic::processCommand(const HandlerPtr &handler, const Cmd &cmd)
{
    if (handler->cmdsSize() == 0) {
        handler->openLog();
    }
    if (Handler::isOpenedBracket(cmd)) {
        handler->pushOpenedBracket();
        handler->processBulk();
        handler->setState(StateBasePtr{new StateDynamic});
    } else {
        handler->pushCmd(cmd);
        if (handler->cmdsSize() == handler->bulkSize()) {
            handler->processBulk();
        }
    }
}

void StateStatic::processEof(const HandlerPtr &handler)
{
    handler->processBulk();
}

void StateDynamic::processCommand(const HandlerPtr &handler, const Cmd &cmd)
{
    if (handler->cmdsSize() == 0) {
        handler->openLog();
    }
    if (Handler::isClosedBracket(cmd)) {
        handler->popOpenedBracket();
        if (handler->bracketsSize() == 0) {
            handler->processBulk();
            handler->setState(StateBasePtr{new StateStatic});
        }
    } else if (Handler::isOpenedBracket(cmd)) {
        handler->pushOpenedBracket();
    } else {
        handler->pushCmd(cmd);
    }
}

void StateDynamic::processEof(const HandlerPtr &handler)
{
    handler->closeLog();
}


