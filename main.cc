#include <memory>
#include <iostream>
//#include "/usr/include/memory.h"
#include "possible_values.h"
#include "sudoku.h"

/**
 * function: solve
 * This method solves the sudoku puzzle utilizing unique pointer for memory management.
 * General algorithm is to recursively try to solve the puzzle by trying each possible value
 * of the cell with lowest possible value count.
 */
std::unique_ptr<Sudoku>
solve(std::unique_ptr<Sudoku> sudoku_puzzle)
{
    if (sudoku_puzzle == nullptr || S->isSolved())
    {
        return sudoku_puzzle;
    }

    int lowest_count_cell = sudoku_puzzle->findCellWithLeastPossibleValues();
    PossibleValues possible_values_set = sudoku_puzzle->getPossibleValuesAtCell(lowest_count_cell);
    for (int i = 1; i <= 9; i++)
    {
        if (possible_values_set.isAvailableValue(i))
        {
            std::unique_ptr<Sudoku> new_sudoku_puzzle(new Sudoku(*sudoku_puzzle));
            if (new_sudoku_puzzle->assignValueToCell(lowest_count_cell))
            {
                // assigning value to cell successful; switch ownership to updated puzzle and try to solve again
                if (auto new_sudoku_puzzle_updated = solve(std::move(new_sudoku_puzzle))
                {
                    return new_sudoku_puzzle_updated;
                }
            }
        }
    }

    return {};
}

int main(int argc, char** argv)
{
    Sudoku::init();
    std::string sudoku_puzzle_input;
    while (getline(std::cin, sudoku_puzzle_input))
    {
        if (auto solved_sudoku_puzzle = solve(std::unique_ptr<Sudoku>(new Sudoku(sudoku_puzzle_input))))
        {
            solved_sudoku_puzzle->printCells();
        }
        else
        {
            std::cout << "No solution found!" << std::endl;
        }

        std::cout << std::endl;
    }
    return 0;
}
