#ifndef SUDOKU_TRY_1_TABLE_H
#define SUDOKU_TRY_1_TABLE_H

#include <cstdint>
#include <exception>
#include <string>
#include <cstring>
#include <array>

class Table
{
protected:
    class Cell
    {
        uint8_t mubValue     = INVALID_VALUE;
        bool    mbIsClear   = true;
        bool    mbIsFixed   = false;
    public:
        Cell(){};
        Cell(uint8_t value)
        {
            set(value);
        }
        bool operator==(Cell& rhs) const
        {
            return (this->mubValue == rhs.mubValue);
        }
        bool operator==(uint8_t rhs) const
        {
            return (this->mubValue == rhs);
        }
        void set(uint8_t value, bool isFixed = false)
        {
            if(((0 < value) && (9 >= value)) || (INVALID_VALUE == value))
            {
                mubValue  = value;
                mbIsFixed = isFixed;
                mbIsClear = false;
            }
            else
            {
                throw InvalidValue(value);
            }
        }
        uint8_t get() const
        {
            return mubValue;
        }
        void clear()
        {
            mubValue  = INVALID_VALUE;
            mbIsClear = true;
        }
        bool isClear() const
        {
            return mbIsClear;
        }
        bool isFixed() const
        {
            return mbIsFixed;
        }
        static constexpr uint8_t INVALID_VALUE = (static_cast<uint8_t>(-1));
    private:
        class InvalidValue : public std::exception
        {
            static char error_string[100];
            const char * what () const throw () {
                sprintf(InvalidValue::error_string,
                        "Invalid value entered for cell - %d (valid values are 1..9)", _val);
                return InvalidValue::error_string;
            }
            uint8_t _val;
        public:
            InvalidValue(uint8_t value)
            : _val(value)
            {}
        };
    };

protected:
    static constexpr uint8_t UNIQVALS = 9;
    typedef std::array<const Table::Cell *, UNIQVALS> CellPtrArray9_t;

private: /* Start class private members */
    std::array<std::array<Cell, UNIQVALS>, UNIQVALS> moCells;


public:
    void setCellValueAt(int col, int row, uint8_t value, bool isFixed = false)
    {
        moCells.at(col).at(row).set(value, isFixed);
    }
    void clearCellAt(int col, int row)
    {
        moCells.at(col).at(row).clear();
    }
    uint8_t getCellValueAt(int col, int row) const
    {
        return cellAt(col, row)->get();
    }
    bool isCellFixedAt(uint8_t col, uint8_t row) const
    {
        return cellAt(col, row)->isFixed();
    }
    const Cell* cellAt(int col, int row) const
    {
        return &moCells.at(col).at(row);
    }
    CellPtrArray9_t rowFor(int col, int row)
    {
        CellPtrArray9_t ret_val = {};

        for(uint8_t i = 0u; i < UNIQVALS; i++)
        {
            ret_val[i] = &moCells[i][row];
        }

        return ret_val;
    }

    CellPtrArray9_t colFor(int col, int row)
    {
        CellPtrArray9_t ret_val = {};

        for(uint8_t i = 0u; i < UNIQVALS; i++)
        {
            ret_val[i] = &moCells[col][i];
        }

        return ret_val;
    }

    CellPtrArray9_t squareFor(int col, int row)
    {
        static std::array<std::array<uint8_t, 3>, 3> indexes =
                {{0,1,2,3,4,5,6,7,8}};

        CellPtrArray9_t ret_val = {};
        auto col_idx = &indexes.at(static_cast<int>(col / 3));
        auto row_idx = &indexes.at(static_cast<int>(row / 3));
        uint8_t idx = 0;

        for(auto _row : *row_idx)
        {
            for(auto _col : *col_idx)
            {
                ret_val[idx++] = &moCells.at(_col).at(_row);
            }
        }

        return ret_val;
    }
};

char Table::Cell::InvalidValue::error_string[100];

#endif //SUDOKU_TRY_1_TABLE_H
