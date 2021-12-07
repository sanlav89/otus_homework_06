#include "state.h"
#include "bulk.h"

using namespace bulk;

void StateStatic::processCommand(Handler *handler, const Cmd &cmd)
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

void StateStatic::processEof(Handler *handler)
{
    handler->processBulk();
}

void StateDynamic::processCommand(Handler *handler, const Cmd &cmd)
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

void StateDynamic::processEof(Handler *handler)
{
    handler->closeLog();
}


