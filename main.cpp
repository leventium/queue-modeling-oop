#define _CRT_SECURE_NO_WARNINGS
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
    kass[0] = queue[0];
    control.printQueue(kass, queue);
    return 0;
}