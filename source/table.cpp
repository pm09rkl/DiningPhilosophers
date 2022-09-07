#include "table.h"

namespace mt
{
    CTable::CTable(std::size_t numSeats)
    {
        for (std::size_t numSeat = 0; numSeat < numSeats; numSeat++)
        {
            _philosophers.emplace_back(numSeat);
            _forks.emplace_back(numSeat);
        }
    }    
}
