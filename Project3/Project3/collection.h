#ifndef COLLECTION
#define COLLECTION

template <typename T>
class UnitsCollection
{
private:
    struct node
    {
        T info;
        node* next;
    };
    node* first;
public:
    UnitsCollection();
    ~UnitsCollection();
    int size() const;
    const T& operator[](const int& i) const;
    void operator<<(const T& right);
    void insert(const int& i, const T& right);
    void del(const int& i);
    void delAll();
    void printAll() const;
};

#endif COLLECTION
