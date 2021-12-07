#include <iostream>
#include "units.h"

int main()
{
    QueueUnit test;
    test.setNumber(1);
    test.setType(2);
    test.setUnique(30);
    std::cout << test.getNumber() << std::endl << test.getType() << std::endl << test.getUnique() << "\n\n";
    
    StatUnit tt(test, 1);
    std::cout << tt.getNumber() << "\n" << tt.getType() << "\n" << tt.getUnique() << "\n\n\n";
    return 0;
}