#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>
#include "table.h"

namespace mt
{
    class CTable;
    
    class CWaiter
    {
    public:
        void serve(CTable& table);
        
    private:
        class CWaiterForSeat
        {
        public:
            typedef std::deque<CWaiterForSeat> List;

        public:
            CWaiterForSeat(std::size_t numSeat);
            
        public:
            void giveForks(std::mutex& mutex, CWaiterForSeat::List& waiters);
            void takeForks(std::mutex& mutex, CWaiterForSeat::List& waiters);
            
        private:
            std::size_t getLeftNumSeat(const CWaiterForSeat::List& waiters) const
                { return (_numSeat - 1 + waiters.size()) % waiters.size(); }

            std::size_t getRightNumSeat(const CWaiterForSeat::List& waiters) const
                { return (_numSeat + 1) % waiters.size(); }
                
        private:
            bool isPhilosopherEating() const
                { return _philosopherState == EPhilosopherState::EATING; }
                
            bool isPhilosopherHungry() const
                { return _philosopherState == EPhilosopherState::HUNGRY; }

            bool isLeftForkFree(const CWaiterForSeat::List& waiters) const
                { return !waiters[getLeftNumSeat(waiters)].isPhilosopherEating(); }

            bool isRightForkFree(const CWaiterForSeat::List& waiters) const
                { return !waiters[getRightNumSeat(waiters)].isPhilosopherEating(); }

        private:
            enum EPhilosopherState
            {
                THINKING = 0,
                HUNGRY,
                EATING
            };
            
        private:
            std::size_t _numSeat;
            EPhilosopherState _philosopherState;
            std::condition_variable _forksFreeCondition;
        };    
        
    private:
        void giveForks(std::size_t numSeat);
        void takeForks(std::size_t numSeat);
        
        void runServeLoopForSeat(CTable& table, std::size_t numSeat);
        void runServeLoop(CTable& table);
        void setWaiters(const CTable& table);
        
    private:
        std::mutex _mutex;
        CWaiterForSeat::List _waiters;
    };    
}
