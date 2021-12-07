#include "units.h"

void OfferUnit::setNumber(int number)
{
    this->number = number;
}
int OfferUnit::getNumber() const
{
    return this->number;
}
void OfferUnit::setType(int type)
{
    this->type = type;
}
int OfferUnit::getType() const
{
    return this->type;
}
void OfferUnit::setUnique(int info)
{
    this->stInfo = info;
}
int OfferUnit::getUnique() const
{
    return this->stInfo;
}


int QueueUnit::getUnique() const
{
    return this->time;
}
void QueueUnit::setUnique(int time)
{
    this->time = time;
}


StatUnit::StatUnit(const QueueUnit &right, int flag)
{
    this->setNumber(right.getNumber());
    this->setType(right.getType());
    this->setUnique(flag);
}
int StatUnit::getUnique() const
{
    return this->status;
}
void StatUnit::setUnique(int status)
{
    this->status = status;
}