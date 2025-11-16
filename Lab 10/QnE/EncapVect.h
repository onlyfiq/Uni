#ifndef ENCAPVECT_H_INCLUDED
#define ENCAPVECT_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <vector>

using std::out_of_range;
using std::vector;

template <class T>
class Vector
{
public:
    Vector();
    Vector(int n);

    bool Add(const T& value);
    bool Insert(int index, const T& value);
    bool Delete(int index);
    int GetSize() const;

    T& operator[](int index);
    const T& operator[](int index) const;

private:
    vector<T> m_data;
};

template <class T>
Vector<T>::Vector()
{
}

template <class T>
Vector<T>::Vector(int n)
{
    if(n > 0)
    {
        m_data.resize(n);
    }
}

template <class T>
bool Vector<T>::Add(const T& value)
{
    try
    {
        m_data.push_back(value);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

template <class T>
bool Vector<T>::Insert(int index, const T& value)
{
    if (index < 0 || index > m_data.size())
    {
        return false;
    }

    try
    {
        m_data.insert(m_data.begin() + index, value);
    }
    catch(...)
    {
        return false;
    }

    return true;
}

template <class T>
bool Vector<T>::Delete(int index)
{
    if (index < 0 || index >= m_data.size())
    {
        return false;
    }
    m_data.erase(m_data.begin() + index);

    return true;
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if(index < 0 || index >= m_data.size())
    {
        throw out_of_range("Index out of bounds");
    }
    return m_data[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if(index < 0 || index >= m_data.size())
    {
        throw out_of_range("Index out of bounds");
    }
    return m_data[index];
}

template <class T>
int Vector<T>::GetSize() const
{
    return m_data.size();
}

#endif // ENCAPVECT_H_INCLUDED
