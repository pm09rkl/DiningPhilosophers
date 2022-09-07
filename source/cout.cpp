#include <iostream>
#include <sstream>
#include <mutex>
#include "cout.h"

namespace mt
{
    void coutLine(const std::string& line)
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << line << std::endl;
    }

    void coutObjectEventLine(const std::string& objectName, std::size_t objectNum, const std::string& eventName)
    {
        std::stringstream stream;
        stream << objectName << " №" << objectNum << " " << eventName;
        coutLine(stream.str());
    }    
}
