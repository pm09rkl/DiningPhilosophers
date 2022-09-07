#include "waiter.h"

int main(int argc, char **argv)
{
    mt::CTable table(5);
    mt::CWaiter waiter;
    waiter.serve(table);
    return 0;
}
