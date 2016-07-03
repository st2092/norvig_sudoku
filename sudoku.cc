#include "sudoku.h"
#include <iostream>

std::vector< std::vector<int> > Sudoku::group(27);
std::vector< std::vector<int> > Sudoku::neighbors(81);
std::vector< std::vector<int> > Sudoku::units(81);

/**
 * Constructor
 * This constructor takes in a string representation of a sudoku puzzle. The string gets use for
 * creating a 9x9 cell representation.
 */
Sudoku::Sudoku(std::string original_sudoku_puzzle)
: cells(81)
{
    std::cout << "Input:\n" << original_sudoku_puzzle << std::endl;
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
    for (int i = 0; i < MAX_POSSIBLE_VALUES; i++)
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
            for (int j = 0; j < MAX_POSSIBLE_VALUES; j++)
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
 * function: getPossibleValuesAtCell
 * Returns the set of possible values a specific cell can be.
 */
PossibleValues
Sudoku::getPossibleValuesAtCell(int cell_number) const
{
    return cells[cell_number];
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
        if (possible_values_count == 0)
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
                if (!removeValueAtCell(neighbors[cell_number][i], correct_cell_value))
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

    return true;
}

/**
 * function: isSovled
 * Determines if the sudoku puzzle is solved.
 * @return bool         true if complete; false otherwise
 */
bool
Sudoku::isSolved() const
{
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].count() != 1)
        {
            return false;
        }
    }

    return true;
}

/**
 * function: assignValueToCell
 * Assign a value to a cell and remove all other values from the cell's possible value set.
 * This method is use only when it is certain the cell should be a certain value.
 */
bool
Sudoku::assignValueToCell(int cell_number, int value)
{
    for (int i = 1; i <= 9; i++)
    {
        if (i != value)
        {
            if (!removeValueAtCell(cell_number, i))
            {
                // failed to remove a value from set
                return false;
            }
        }
    }

    return true;
}

/**
 * function: findCellWithLeastPossibleValues
 * Traverse though all cells and returns the last found cell index with the least possible
 * values.
 */
int
Sudoku::findCellWithLeastPossibleValues() const
{
    int minimum_possible_values = 0;
    int cell_with_lowest_possible_values = -1;

    int current_cell_min_possible_values = 0;
    for (int i = 0; i < cells.size(); i++)
    {
        current_cell_min_possible_values = cells[i].count();

        if (current_cell_min_possible_values > 1 && (current_cell_min_possible_values < minimum_possible_values || cell_with_lowest_possible_values == -1))
        {
            minimum_possible_values = current_cell_min_possible_values;
            cell_with_lowest_possible_values = i;
        }
    }

    return cell_with_lowest_possible_values;
}

void
Sudoku::printCells(std::ostream & output_stream) const
{
    int width = 1;
    for (int i = 0; i < cells.size(); i++)
    {
        width = std::max(width, 1 + cells[i].count());
    }

    const std::string separator(3 * width, '-');
    for (int i = 0; i < MAX_POSSIBLE_VALUES; i++)
    {
        if (i == 3 || i == 6)
        {
            output_stream << separator << "+-" << separator << "+" << separator << std::endl;
        }
        
        for (int j = 0; j < MAX_POSSIBLE_VALUES; j++)
        {
            if (j == 3 || j == 6)
            {
               output_stream << "| "; 
            }
	    output_stream << cells[i*9 + j].toString(width);
        }
        output_stream << std::endl;
    }
}
