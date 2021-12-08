#ifndef KASSES
#define KASSES

#include "units.h"

class Kasses
{
private:
    int amount;
    QueueUnit kas0, kas1, kas2, kas3, kas4;
public:
    Kasses();
    int getAmount() const;
    void setAmount(int amount);
    QueueUnit& operator[](const int &i);
};

#endif KASSES