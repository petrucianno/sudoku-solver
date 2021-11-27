#include "Utilites.h"

#include <cstdlib>
#include <ctime>

int randint(int from, int to)
{
    static bool init = false;
    int ret_val = 0;
    if (!init)
    {
        srand(time(nullptr) * from + to);
        init = true;
    }
    ret_val = rand() % to + from;
    return ret_val;
}
