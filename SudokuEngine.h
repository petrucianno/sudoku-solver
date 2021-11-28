#ifndef SUDOKU_TRY_1_SUDOKUENGINE_H
#define SUDOKU_TRY_1_SUDOKUENGINE_H

#include <cstdint>
#include <array>
#include <algorithm>
#include <functional>
#include <random>

#include "Table.h"

class SudokuEngine : public Table
{
    void fillDiagonal()
    {
        static std::array<uint8_t, UNIQVALS> numbers =
                {{1,2,3,4,5,6,7,8,9}};

        static std::random_device rd;
        static std::mt19937 g(rd());

        for (auto i = 0; i < 3; i++)
        {
            std::shuffle(numbers.begin(), numbers.end(), g);

            for (auto j = 0; j < UNIQVALS; j++)
            {
                int r = (j / 3) + (3 * i);
                int c = (j % 3) + (3 * i);

                this->setCellValueAt(c, r, numbers.at(j), true);
            }
        }
    }

    bool testCellForValue(int col, int row, uint8_t value)
    {
        auto row_nbh    = rowFor(col, row);
        auto col_nbh    = colFor(col, row);
        auto square_nbh = squareFor(col, row);
        auto has_value  = [value](const CellPtrArray9_t &vector)
        {
            return (vector.end() != std::find_if(vector.begin(), vector.end(),
                                                 [value](const Table::Cell *c){ return (*c) == value; }) );
        };

        if ( has_value(row_nbh) || has_value(col_nbh) || has_value(square_nbh) )
        {
            return false;
        }

        return true;
    }

    uint8_t findCellValue(uint8_t col, uint8_t row, uint8_t value)
    {
        if (((UNIQVALS <= col) && (UNIQVALS <= row)) || (UNIQVALS < value))
        {
            return Cell::INVALID_VALUE;
        }
        if (testCellForValue(col, row, value))
        {
            return value;
        }
        return findCellValue(col, row, value + 1);
    };

    void solve()
    {
        bool backtrack = false;
        std::function<bool(uint8_t, uint8_t, uint8_t, uint64_t&)> findSolution;
        findSolution = [this, &backtrack, &findSolution](uint8_t col, uint8_t row, uint8_t value, uint64_t &recursionLevel){

//            auto lCol = col, lRow = row;
//            auto cellValue = 1;
            do
            {
                auto lCol = col, lRow = row;
                auto cellValue = 1;

                //std::cout << "0. col:" << (int)lCol << " row:" << (int)lRow << " backtrack:" << backtrack << std::endl;
                if ((UNIQVALS <= lCol) && (UNIQVALS - 1 <= lRow))
                {
                    return true;
                }
                if (UINT8_MAX <= lCol)
                {
                    lRow -= 1;
                    lCol = UNIQVALS - 1;
                }
                if (UNIQVALS <= lCol)
                {
                    lRow += 1;
                    lCol = 0;
                }

                //std::cout << "1. col:" << (int)lCol << " row:" << (int)lRow << " backtrack:" << backtrack << std::endl;
                if (backtrack)
                {
                    if (!cellAt(lCol, lRow)->isFixed())
                    {
                        /* If its value isn't fixed, stop */
                        backtrack = false;
                        if (!cellAt(lCol, lRow)->isClear())
                            cellValue = getCellValueAt(lCol, lRow) + 1;
                        else
                            cellValue = 1;
                        clearCellAt(lCol, lRow);
                    }
                    else
                    {
                        /* Go back more */
                        lCol -= 1;
                    }
                }
                else
                {
                    /**/if ( (0u == (recursionLevel % 200)) && (0u != recursionLevel) )
                    {
                        lCol -= 1;
                        backtrack = true;
                    }
                    else if (!isCellFixedAt(lCol, lRow))
                    {
                        cellValue = findCellValue(lCol, lRow, value);

                        if (Cell::INVALID_VALUE != cellValue)
                        {
                            setCellValueAt(lCol, lRow, cellValue);
                            lCol += 1;
                        }
                        else
                        {
                            lCol -= 1;
                            backtrack = true;
                        }
                        cellValue = 1;
                    }
                    else
                    {
                        lCol += 1;
                    }
                }

                //std::cout << "2. col:" << (int)lCol << " row:" << (int)lRow << " backtrack:" << backtrack << " val:" << (int)cellValue << std::endl;
                //std::cout << "Rec lvl: " << recursionLevel << std::endl;
                col = lCol, row = lRow, value = cellValue, recursionLevel += 1;
            } while (true);
            //return findSolution(lCol, lRow, cellValue, recursionLevel + 1);
        };
        try
        {
            uint64_t recursions = 0;
            auto done = findSolution(0, 0, 1, recursions);
            std::cout << (done?"Done":"Sorry") << ", "+std::to_string(recursions) << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "Sorry :/" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }

    void print()
    {
        std::cout << "---" << std::endl;
        for (int i = 0; i < UNIQVALS; i++)
        {
            for (int j = 0; j < UNIQVALS; j++)
            {
                auto val = (int)getCellValueAt(j, i);
                auto str = "|" + std::to_string(val) + "|";
                std::cout << (val==Cell::INVALID_VALUE ? "|_|" : str) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "---" << std::endl;
    }

public:
    SudokuEngine(){
        fillDiagonal();
        //print();
        solve();
        //print();
    }

    SudokuEngine(const std::array<std::array<int, UNIQVALS>, UNIQVALS> & tst )
    {
        for (int row = 0; row < UNIQVALS; row++)
        {
            for (int col = 0; col < UNIQVALS; col++)
            {
                bool isFixed = tst.at(row).at(col) != Cell::INVALID_VALUE;
                setCellValueAt(col, row, tst.at(row).at(col), isFixed);
            }
        }
        //print();
        solve();
        //print();
    }
};

#endif //SUDOKU_TRY_1_SUDOKUENGINE_H
