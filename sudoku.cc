#include "sudoku.h"

/**
 * Constructor
 * This constructor takes in a string representation of a sudoku puzzle. The string gets use for
 * creating a 9x9 cell representation.
 */
Sudoku::Sudoku(string original_sudoku_puzzle)
: cells(81)
{
    int cell_number = 0;
    for (int i = 0; i < cells.size(); i++)
    {
        if (original_sudoku_puzzle[i] >= '1' && original_sudoku_puzzle[i] <= '9')
        {
            if (!assignValueToCell(cell_number, original_sudoku_puzzle[i] - '0'))
            {
                std::cerr << "Error loading in sudoku puzzle. Please check formatting." << std::endl;
                return;
            }
            cell_number++;
        }
        else if (original_sudoku_puzzle[i] == '0' || original_sudoku_puzzle[i] == '.')
        {
            cell_number++;
        }
    }
}


