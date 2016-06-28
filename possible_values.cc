#include "possible_values.h"

/**
 * Constructor
 */ 
PossibleValues::PossibleValues()
: values_to_choose(9, true)
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
