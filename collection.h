template <typename T>
class UnitsCollection
{
private:
    struct node
    {
        T info;
        node *next;
    };
    node *first;
public:
    UnitsCollection();
    ~UnitsCollection();
    int size();
    const T& operator[](const int &i);
    void operator<<(const T &right);
    void insert(const int &i, const T &right);
    void del(const int &i);
};