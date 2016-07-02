#ifndef _POSSIBLE_VALUES_H_
#define _POSSIBLE_VALUES_H_

#include <vector>
#include <string>
#include <algorithm>

static const int MAX_POSSIBLE_VALUES = 9;

class PossibleValues
{
private:
    std::vector<bool> values_to_choose;

public:
    PossibleValues();
    bool   isAvailableValue(const int & value) const;
    int    count() const;
    void   removeValue(const int & value);
    int    getCorrectValue() const;
    std::string toString(const int & width) const;
};

#endif
