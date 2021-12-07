class OfferUnit
{
private:
    int number, type;
    int stInfo;
public:
    void setNumber(int number);
    int getNumber() const;
    void setType(int type);
    int getType() const;
    virtual void setUnique(int info);
    virtual int getUnique() const;
};

class QueueUnit : public OfferUnit
{
private:
    int time;
public:
    virtual void setUnique(int time);
    virtual int getUnique() const;
};

class StatUnit : public OfferUnit
{
private:
    int status;
public:
    StatUnit(const QueueUnit &right, int flag);
    virtual void setUnique(int status);
    virtual int getUnique() const;
};