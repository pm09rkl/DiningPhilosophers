#include "cout.h"
#include "fork.h"

namespace mt
{
    CFork::CFork(std::size_t num)
        : _num(num)
    {
    }

    void CFork::up()
    {
        coutObjectEventLine("Fork", _num, "is up");
    }    
}
