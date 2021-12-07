#include "units.h"

void OfferUnit::setNumber(int number)
{
    this->number = number;
}
int OfferUnit::getNumber()
{
    return this->number;
}
void OfferUnit::setType(int type)
{
    this->type = type;
}
int OfferUnit::getType()
{
    return this->type;
}
void OfferUnit::setUnique(int info)
{
    this->stInfo = info;
}
int OfferUnit::getUnique()
{
    return this->stInfo;
}


int QueueUnit::getUnique()
{
    return this->time;
}
void QueueUnit::setUnique(int time)
{
    this->time = time;
}


int StatUnit::getUnique()
{
    return this->status;
}
void StatUnit::setUnique(int status)
{
    this->status = status;
}