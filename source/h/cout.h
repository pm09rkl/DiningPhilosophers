#pragma once

#include <string>

namespace mt
{
    // thread-safe cout
    void coutLine(const std::string& line);
    void coutObjectEventLine(const std::string& objectName, std::size_t objectNum, const std::string& eventName);
}
