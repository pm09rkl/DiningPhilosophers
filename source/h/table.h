#pragma once

#include "fork.h"
#include "philosopher.h"

namespace mt
{
    class CTable
    {
    public:
        CTable(std::size_t numSeats);

    public:
        const CPhilosopher& getPhilosopher(std::size_t numSeat) const
            { return _philosophers[numSeat]; }

        CPhilosopher& getPhilosopher(std::size_t numSeat)
            { return _philosophers[numSeat]; }

    public:
        const CFork& getLeftFork(std::size_t numSeat) const
            { return _forks[getLeftForkNum(numSeat)]; }

        CFork& getLeftFork(std::size_t numSeat)
            { return _forks[getLeftForkNum(numSeat)]; }

        const CFork& getRightFork(std::size_t numSeat) const
            { return _forks[getRightForkNum(numSeat)]; }

        CFork& getRightFork(std::size_t numSeat)
            { return _forks[getRightForkNum(numSeat)]; }

    public:
        std::size_t getNumSeats() const
            { return _philosophers.size(); }

    private:
        std::size_t getLeftForkNum(std::size_t numSeat) const
            { return numSeat; }
            
        std::size_t getRightForkNum(std::size_t numSeat) const
            { return (numSeat + 1) % _forks.size(); }
        
    private:
        CPhilosopher::List _philosophers;
        CFork::List _forks;
    };
}
