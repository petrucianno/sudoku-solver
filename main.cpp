#include <iostream>

#include <vector>
#include <algorithm>

#include "SudokuEngine.h"
constexpr uint8_t NA = (static_cast<uint8_t>(-1));
int main()
{
    std::array<std::array<int, 9>, 9> tst =
            {{
                     NA, 	NA, 	NA, 	4, 	    6, 	    NA, 	NA, 	7, 	    1,
                     7, 	NA, 	NA, 	NA, 	1, 	    8, 	    NA, 	NA, 	NA,
                     NA, 	NA, 	6, 	    NA, 	7, 	    NA, 	NA, 	NA, 	NA,
                     NA, 	NA, 	NA, 	NA, 	4, 	    NA, 	7, 	    3, 	    NA,
                     NA, 	8, 	    NA, 	NA, 	NA, 	NA, 	2, 	    4, 	    NA,
                     4, 	2, 	    NA, 	NA, 	NA, 	9, 	    NA, 	NA, 	NA,
                     NA, 	6, 	    8, 	    NA, 	9, 	    NA, 	NA, 	NA, 	4,
                     NA, 	NA, 	5, 	    6,  	NA, 	NA, 	NA, 	1, 	    NA,
                     NA, 	NA, 	2, 	    1, 	    NA, 	NA, 	NA, 	5, 	    NA

             }};
    SudokuEngine table1;
    SudokuEngine table2(tst);
    return 0;
}
