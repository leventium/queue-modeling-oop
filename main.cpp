#include <iostream>
#include "collection.cpp"
#include "control.h"
#include "kasses.h"
#include "units.h"
int main()
{
    Kasses kass;
    UnitsCollection<QueueUnit> queue; 
    UnitsCollection<StatUnit> stat;
    int n = 0;
    Control control;
    control.enter(kass, queue, stat, n);
    queue.printAll();
    return 0;
}