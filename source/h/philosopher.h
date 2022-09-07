#pragma once

#include <vector>
#include <random>

namespace mt
{
    class CFork;
    
    class CPhilosopher
    {
    public:
        typedef std::vector<CPhilosopher> List;
        
    public:
        CPhilosopher(std::size_t num);

    public:
        void eat(CFork& leftFork, CFork& rightFork);
        void think();
        
    private:
        void sleep();

    private:
        std::size_t _num;
        std::default_random_engine _randomEngine;
        std::uniform_int_distribution<int> _randomMilliseconds;
    };    
}
