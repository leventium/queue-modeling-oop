#include <iostream>
#include "units.h"
//#include "collection.h"
#include "control.h"
//#include "kirill_control.cpp"
#include "collection.cpp"
#include "kasses.h"

int main()
{
    Kasses kass;
    QueueUnit test;
    UnitsCollection<QueueUnit> queue;
    UnitsCollection<StatUnit> stat;
    int n = 0;
    test.setNumber(10);
    kass.setAmount(3);
    kass[0] = test;
    
    std::cout << kass[2].getNumber() << "\n\n";

    Control control;
    control.enter(kass, queue, stat, n);
    return 0;
}