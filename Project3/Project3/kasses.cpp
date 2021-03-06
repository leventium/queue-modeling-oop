#include "kasses.h"

Kasses::Kasses()
{
    amount = 0;
}
int Kasses::getAmount() const { return amount; }
void Kasses::setAmount(int amount)
{
    if (amount >= 1 && amount <= 5)
        this->amount = amount;
    else
        throw "invalid argument";
}
QueueUnit& Kasses::operator[](const int& i)
{
    if (amount && i >= 0 && i <= amount - 1)
    {
        switch (i)
        {
        case 0:
            return kas0;
            break;
        case 1:
            return kas1;
            break;
        case 2:
            return kas2;
            break;
        case 3:
            return kas3;
            break;
        case 4:
            return kas4;
            break;
        default:
            throw "index out of range";
        }
    }
    else
        throw "index out of range";
}