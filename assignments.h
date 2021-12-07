#pragma once

#include <string>
#include <memory>

namespace bulk {

using Cmd = std::string;
using Bracket = char;

class HandlerCore;
using HandlerCorePtr = std::shared_ptr<HandlerCore>;

}

