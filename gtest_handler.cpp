#include <gtest/gtest.h>

#include <iostream>
#include "handler.h"

// Demonstrate some basic assertions.
TEST(HandlerTest, Functionality)
{
    std::istringstream iss("cmd1\n");
    std::ostringstream oss;
    bulk::Handler handler(3, iss);
    handler.registerLogger(logger::LogPtr{new logger::Console(oss)});
    handler.start();
    EXPECT_TRUE(oss.str() == "bulk: cmd1\n");
}
