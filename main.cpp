#include <iostream>
#include "units.h"
#include "collection.h"
#include "control.h"
#include "collection.cpp"
#include "kasses.h"

int main()
{
    Kasses kass;
    QueueUnit test;
    test.setNumber(10);
    kass.setAmount(10);
    kass[0] = test;
    
    std::cout << kass[2].getNumber() << "\n\n";
    return 0;
}