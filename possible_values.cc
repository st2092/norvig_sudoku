#include "possible_values.h"

/**
 * Constructor
 */ 
PossibleValues::PossibleValues()
: values_to_choose(MAX_POSSIBLE_VALUES, true)
{
    // do nothing
}

/**
 * function: isAvailableValue
 * This method takes in a value between 1 to 9 and returns whether or not it
 * is available.
 */
bool
PossibleValues::isAvailableValue(const int & value) const
{
    return values_to_choose[value - 1];
}

/**
 * function: count
 * This method returns how many possible values is remaining.
 */
int
PossibleValues::count() const
{
    int number_of_possible_values = std::count(values_to_choose.begin(), values_to_choose.end(), true);

    return number_of_possible_values;
}

/**
 * function: removeValue
 * This method removes the specified value from the set of possible values.
 */
void
PossibleValues::removeValue(const int & value)
{
    values_to_choose[value - 1];
}

/**
 * function: getCorrectValue
 * This method returns the determined value of this object in the sudoku puzzle.
 * @return int          correct value if true; -1 otherwise
 */ 
int
PossibleValues::getCorrectValue() const
{
    auto correct_value_iterator = find(values_to_choose.begin(), values_to_choose.end(), true);

    return (correct_value_iterator != values_to_choose.end() ? 
            1 + (correct_value_iterator - values_to_choose.begin()) : -1);
}

/**
 * function: toString
 * Converts the possible value set into a string representation.
 */
std::string
PossibleValues::toString(const int & width) const
{
    std::string possible_values_str(width, ' ');

    for (int i = 0; i < MAX_POSSIBLE_VALUES; i++)
    {
       if (isAvailableValue(i))
       {
           possible_values_str[i] = '0' + i;
       } 
    }

    return possible_values_str;
}
