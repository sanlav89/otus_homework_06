#include <iostream>
#include <cassert>
#include "handler.h"

int main(int argc, char *argv[])
{
//    std::cout << "Hello from Bulk!" << std::endl;
//    std::cout << "You can simulate EOF with CTRL+D (for *nix) or CTRL+Z (for Windows) from command line." << std::endl;

    assert(argc == 2);
    int bulkSize = std::atoi(argv[1]);
    assert(bulkSize > 0);

    bulk::Handler handler(bulkSize);
    handler.registerLogger(logger::LogPtr{new logger::Console()});
    handler.registerLogger(logger::LogPtr{new logger::LogFile()});

    std::string cmd;
    while (std::getline(std::cin, cmd)) {
        handler.addCommand(cmd);
    }
    handler.addCommandEof();

    return 0;
}
