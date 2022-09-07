#include <thread>
#include "fork.h"
#include "cout.h"
#include "philosopher.h"

namespace mt
{
    CPhilosopher::CPhilosopher(std::size_t num)
        : _num(num)
        , _randomMilliseconds(10, 200)
    {
    }

    void CPhilosopher::eat(CFork& leftFork, CFork& rightFork)
    {
        leftFork.up();
        rightFork.up();
        coutObjectEventLine("Philosopher", _num, "start eating");
        sleep();
        coutObjectEventLine("Philosopher", _num, "stop eating and want to think");
    }

    void CPhilosopher::think()
    {
        coutObjectEventLine("Philosopher", _num, "start thinking");
        sleep();
        coutObjectEventLine("Philosopher", _num, "stop thinking and hungry");
    }

    void CPhilosopher::sleep()
    {
        int milliseconds = _randomMilliseconds(_randomEngine);
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }    
}
