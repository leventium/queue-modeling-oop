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
    UnitsCollection();                          //конструктор
    ~UnitsCollection();                         //деструктор
    int size();                                 //возвращает размер массива
    const T& operator[](const int &i);          //возвращает ссылку на запрошенный элемент
    void operator<<(const T &right);            //добавляет переданный элемент в конец
    void insert(const int &i, const T &right);  //всталяет новый элемент на указанное место
    void del(const int &i);                     //удаляет указанный элемент
};