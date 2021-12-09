#include "collection.h"

template <typename T>
UnitsCollection<T>::UnitsCollection()
{
    first = nullptr;
}
template <typename T>
UnitsCollection<T>::~UnitsCollection()
{
    node *now = first, *sled;
    while (now != nullptr)
    {
        sled = now->next;
        delete now;
        now = sled;
    }
}
template <typename T>
int UnitsCollection<T>::size() const
{
    node *now = first;
    int i = 0;
    while (now != nullptr)
    {
        ++i;
        now = now->next;
    }
    return i;
}
template <typename T>
const T& UnitsCollection<T>::operator[](const int &i) const
// &i - index
{
    node *now = first;
    if (now != nullptr)
    {
        int ind = 0;
        while (ind < i)
        {
            now = now->next;
            ++ind;
        }
        if (now != nullptr)
            return now->info;
        else
            throw "index out of range";
    }
    else
        throw "index out of range";
    
}
template <typename T>
void UnitsCollection<T>::operator<<(const T &right)
// &right - new element   
{
    if (first != nullptr)
    {
        node *now = first;
        while (now->next != nullptr) now = now->next;
        node *elem = new node;
        elem->info = right;
        elem->next = nullptr;
        now->next = elem;
    }
    else
    {
        first = new node;
        first->info = right;
        first->next = nullptr;
    }
}
template <typename T>
void UnitsCollection<T>::insert(const int &i, const T &right)
// &i - index, &right - new element
{
    if (first != nullptr)
    {
        node *now = first;
        int ind = 0;
        while (ind < i - 1)
        {
            now = now->next;
            ++ind;
        }
        if (now != nullptr)
        {
            node *elem = new node;
            elem->info = right;
            elem->next = nullptr;
            now->next = elem;
        }
        else
            throw "index out of range";
    }
    else if (i == 0)
    {
        first = new node;
        first->info = right;
        first->next = nullptr;
    }
    else
        throw "index out of range";
}
template <typename T>
void UnitsCollection<T>::del(const int &i)
// &i - index
{
    if (first != nullptr && i >= 0)
    {
        if (i == 0)
        {
            node *now = first->next;
            delete first;
            first = now;
        }
        else
        {
            node *now = first;
            int ind = 0;
            while (ind < i - 1)
            {
                now = now->next;
                ++ind;
            }
            if (now != nullptr && now->next != nullptr)
            {
                node *sled;
                sled = now->next->next;
                delete now->next;
                now->next = sled;
            }
            else
                throw "index out of range";
        }
    }
    else
        throw "index out of range";
}

template <typename T>
void UnitsCollection<T>::delAll()
{
    if (first!=nullptr)
    {
        node* now = first, * sled;
        while (now != nullptr)
        {
            sled = now->next;
            delete now;
            now = sled;
        }
        first = nullptr;
    }
};