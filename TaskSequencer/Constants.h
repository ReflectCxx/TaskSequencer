#pragma once

#include <cstdint>

namespace hex
{
    enum class BlocksQ {
        No,   // Does not block the queue.
        Yes,  // Blocks the queue while executing.
        Join, // Waits for all running commands to finish, then blocks while executing.
    };
}
namespace hex { enum class CmdState { None, Queued, Ready, Running, Expired }; }
