#include <iostream>
#include "bulk.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello from Bulk!" << std::endl;
    int bulkSize = 0;

    if (argc != 2) {
        std::cout << "Wrong Arguments" << std::endl;
        return 1;
    }

    bulkSize = std::atoi(argv[1]);
    if (bulkSize == 0) {
        std::cout << "Wrong Arguments" << std::endl;
        return 2;
    }

//    std::cout << "You can simulate EOF with CTRL+D (for *nix) or CTRL+Z (for Windows) from command line." << std::endl;

    bulk::BulkHandler handler(bulkSize);
    std::string cmd;
    while (std::getline(std::cin, cmd)) {
        handler.addCommand(cmd);
    }
    handler.addCommandEof();

    return 0;
}
