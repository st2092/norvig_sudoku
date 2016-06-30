#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "possible_values.h"
#include <algorithm>
#include <vector>

class Sudoku
{
private:
    std::vector<PossibleValues> cells;
    bool removeValueAtCell(int cell_number, int value);
    static std::vector< std::vector<int> > group;
    static std::vector< std::vector<int> > unit;        // collection of 9 cells is 1 unit
    static std::vector< std::vector<int> > neighbors;   // cells that share the same group

public:
    Sudoku(string original_sudoku_puzzle);
    void init();
    PossibleValues getPossibleValuesAtCell(int cell_number);
    bool isSolved() const;
    bool assignValueToCell(int cell_number, int value);
    int  findCellWithLeastPossibleValues() const;
    void printCells(ostream & output_stream) const;
};

#endif
