#include <iostream>
#include "units.h"
#include "collection.h"
//#include "collection.cpp"

int main()
{
    /*
    UnitsCollection<int> some;
    some.insert(0, 10);
    std::cout << some[0] << "\n\n";
    */

    QueueUnit a;
    a.setNumber(10);
    std::cout << a.getNumber() << "\n\n";

    UnitsCollection<int> aa;
    return 0;
}