#pragma once

#include <vector>

namespace mt
{
    class CFork
    {
    public:
        typedef std::vector<CFork> List;
        
    public:
        CFork(std::size_t num);
        
    public:
        void up();
        
    private:
        std::size_t _num;    
    };    
}
