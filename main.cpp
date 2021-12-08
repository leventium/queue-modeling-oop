#include <iostream>
#include "units.h"
#include "collection.h"

int main()
{
    UnitsCollection<int> some;
    some.insert(0, 10);
    std::cout << some[0] << "\n\n";
    return 0;
}