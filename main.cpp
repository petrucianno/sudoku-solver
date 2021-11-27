#include <iostream>

#include <vector>
#include <algorithm>

#include "SudokuEngine.h"
constexpr uint8_t NA = (static_cast<uint8_t>(-1));
int main()
{
    std::array<std::array<int, 9>, 9> tst =
            {{
                     NA, 7, NA, NA, NA, 4, NA, NA, NA,
                     NA, NA, 8, NA, NA, 3, 2, NA, 5,
                     5, NA, 6, NA, NA, NA, NA, NA, NA,
                     NA, 2, NA, NA, NA, 2, NA, NA, NA,
                     NA, 8, 3, NA, NA, 2, 1, 9, NA,
                     6, NA, NA, NA, NA, NA, 3, 2, NA,
                     NA, NA, NA, 1, 4, NA, NA, NA, 8,
                     NA, NA, NA, NA, NA, NA, NA, NA, 2,
                     9, NA, NA, NA, NA, NA, 6, 3, 1
            }};
    SudokuEngine table(tst);
    return 0;
}
