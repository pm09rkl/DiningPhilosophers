#include <thread>
#include "waiter.h"

namespace mt
{
    CWaiter::CWaiterForSeat::CWaiterForSeat(std::size_t numSeat)
        : _numSeat(numSeat)
        , _philosopherState(EPhilosopherState::THINKING)
    {
    }
            
    void CWaiter::CWaiterForSeat::giveForks(std::mutex& mutex, CWaiterForSeat::List& waiters)
    {
        std::unique_lock<std::mutex> lock(mutex);
        _philosopherState = EPhilosopherState::HUNGRY;
        _forksFreeCondition.wait(lock, [&]() { return isLeftForkFree(waiters) && isRightForkFree(waiters); });
        _philosopherState = EPhilosopherState::EATING;
    }
            
    void CWaiter::CWaiterForSeat::takeForks(std::mutex& mutex, CWaiterForSeat::List& waiters)
    {
        std::unique_lock<std::mutex> lock(mutex);
        _philosopherState = EPhilosopherState::THINKING;
        CWaiterForSeat& left = waiters[getLeftNumSeat(waiters)];
        CWaiterForSeat& right = waiters[getRightNumSeat(waiters)];
        bool isLeftReadyToEat = left.isPhilosopherHungry() && left.isLeftForkFree(waiters);
        bool isRightReadyToEat = right.isPhilosopherHungry() && right.isRightForkFree(waiters);
        lock.unlock();               
        if (isLeftReadyToEat)
        {
            left._forksFreeCondition.notify_one();
        }
        if (isRightReadyToEat)
        {
            right._forksFreeCondition.notify_one();
        }            
    }

    void CWaiter::giveForks(std::size_t numSeat)
    {
        _waiters[numSeat].giveForks(_mutex, _waiters);
    }
        
    void CWaiter::takeForks(std::size_t numSeat)
    {
        _waiters[numSeat].takeForks(_mutex, _waiters);
    }
        
    void CWaiter::runServeLoopForSeat(CTable& table, std::size_t numSeat)
    {
        CPhilosopher& philosopher = table.getPhilosopher(numSeat);
        CFork& leftFork = table.getLeftFork(numSeat);
        CFork& rightFork = table.getRightFork(numSeat);
        while (true)
        {
            philosopher.think();
            giveForks(numSeat);            
            philosopher.eat(leftFork, rightFork);
            takeForks(numSeat);
        }
    }

    void CWaiter::setWaiters(const CTable& table)
    {
        _waiters.clear();
        for (std::size_t numSeat = 0; numSeat < table.getNumSeats(); numSeat++)
        {
            _waiters.emplace_back(numSeat);
        }    
    }

    void CWaiter::runServeLoop(CTable& table)
    {
        std::vector<std::thread> threads;
        for (std::size_t numSeat = 0; numSeat < table.getNumSeats(); numSeat++)
        {
            threads.push_back(std::thread(&CWaiter::runServeLoopForSeat, this, std::ref(table), numSeat));
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
    }

    void CWaiter::serve(CTable& table)
    {
        setWaiters(table.getNumSeats());
        runServeLoop(table);
    }    
}
