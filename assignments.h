#pragma once

#include <string>
#include <memory>

namespace bulk {

using Cmd = std::string;
using Bracket = char;

class Handler;
using HandlerPtr = std::shared_ptr<Handler>;

}

