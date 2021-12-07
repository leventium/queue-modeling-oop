class OfferUnit
{
private:
    int number, type;
    int stInfo;
public:
    void setNumber(int number);
    int getNumber();
    void setType(int type);
    int getType();
    virtual void setUnique(int info);
    virtual int getUnique();
};

class QueueUnit : public OfferUnit
{
private:
    int time;
public:
    virtual void setUnique(int time);
    virtual int getUnique();
};

class StatUnit : public OfferUnit
{
private:
    int status;
public:
    virtual void setUnique(int status);
    virtual int getUnique();
};