#include <iostream>
#include <cassert>
#include "bulk.h"

int main(int argc, char *argv[])
{
//    std::cout << "Hello from Bulk!" << std::endl;
//    std::cout << "You can simulate EOF with CTRL+D (for *nix) or CTRL+Z (for Windows) from command line." << std::endl;

    assert(argc == 2);
    int bulkSize = std::atoi(argv[1]);
    assert(bulkSize > 0);

    bulk::Handler handler(bulkSize);
    handler.registerLog(log::LogPtr{new log::Console()});
    handler.registerLog(log::LogPtr{new log::LogFile()});

    std::string cmd;
    while (std::getline(std::cin, cmd)) {
        handler.addCommand(cmd);
    }
    handler.addCommandEof();

    return 0;
}
