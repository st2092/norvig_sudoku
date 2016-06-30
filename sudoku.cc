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

void
Sudoku::init()
{
    group(27);
    units(81);
    neighbors(81);

    for (int i = 0; i < MAX_POSSIBLE_VALUE; i++)
    {
        for (int j = 0; j < MAX_POSSIBLE_VALUES; j++)
        {
            int k = i * 9 + j;
            int group_entry[3] = {i, 9 + j, 18 + (i/3) * 3 + j/3};
            for (int g = 0; g < 3; g++)
            {
                group[group_entry[g]].push_back(k);
                units[k].push_back(group_entry[g]);
            }
        }
    }

    for (int k = 0; k < neighbors.size(); k++)
    {
        for (int x = 0; x < units[k].size(); x++)
        {
            for (int j = 0; j < MAX_POSSIBLE_VALUE; j++)
            {
                int k2 = group[units[k][x]][j];
                if (k2 != k)
                {
                    neighbors[k].push_back(k2);
                }
            }
        }
    }
}

/**
 * function: removeValueAtCell
 * This method remove a specified value from a specified cell.
 * After removal, if the correct value is found then the cell's neighbors
 * are updated.
 */
bool
Sudoku::removeValueAtCell(int cell_number, int value)
{
    if (!cells[cell_number].isAvailableValue(value))
    {
        // already removed
        return true;
    }
    else
    {
        cells[cell_number].removeValue(value);

        int possible_values_count = cells[cell_number].count();
        if (possible_values_count <= 0)
        {
            return false;
        }
        else if (possible_values_count == 1)
        {
            // only one possible value left; this must be correct one
            int correct_cell_value = cells[cell_number].getCorrectValue();

            // for all neighbors of cell remove the correct value as a possibility
            for (int i = 0; i < neighbors[cell_number].size(); i++)
            {
                if (!removeValueAtCell([cell_numbe][i], correct_cell_value))
                {
                    return false;
                }
            }
        }
        
        // check if an unit is reduced to only one place for a value, then put it there
        for (int i = 0; i < units[cell_number].size(); i++)
        {
            int unit_id = units[cell_number][i];
            int n = 0;
            int ks;

            for (int j = 0; j < MAX_POSSIBLE_VALUES; j++)
            {
                int p = group[unit_id][j];
                if (cells[p].isAvailableValue(value))
                {
                    n++;
                    ks = p;
                }
            }
            if (n == 0)
            {
                return false;
            }
            else if (n == 1)
            {
                if (!assignValueToCell(ks, value))
                {
                    return false;
                }
            }
        }
    }
}


