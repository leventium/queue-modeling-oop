#include "kasses.h"

int Kasses::getAmount() const { return amount; }
void Kasses::setAmount(int amount) { this->amount = amount; }
QueueUnit& Kasses::operator[](const int &i)
{
    if (!amount && i >= 0 && i <= amount)
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
}