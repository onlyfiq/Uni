#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <map>
#include <stdexcept>
#include "EncapVect.h"

using std::runtime_error;
using std::map;

template <class K, class V>
class Map
{
public:
    Map();

    bool Contains(const K& key) const;
    int Size() const;
    void Clear();

    V& operator[](const K& key);       // main access method
    const V& At(const K& key) const;   // throws if missing

    K KeyAt(int index) const;          // get key by sorted index
    V& ValueAt(int index);             // get value by sorted index
    const V& ValueAt(int index) const;

    void GetKeys(Vector<K>& out) const;

private:
    map<K, V> m_data;
};

template <class K, class V>
Map<K, V>::Map()
{
}

template <class K, class V>
bool Map<K, V>::Contains(const K& key) const
{
    return m_data.find(key) != m_data.end();
}

template <class K, class V>
int Map<K, V>::Size() const
{
    return static_cast<int>(m_data.size());
}

template <class K, class V>
void Map<K, V>::Clear()
{
    m_data.clear();
}

template <class K, class V>
V& Map<K, V>::operator[](const K& key)
{
    return m_data[key]; // creates default value if missing
}

template <class K, class V>
const V& Map<K, V>::At(const K& key) const
{
    typename map<K, V>::const_iterator it = m_data.find(key);
    if (it == m_data.end())
    {
        throw runtime_error("Key not found");
    }
    return it->second;
}

template <class K, class V>
K Map<K, V>::KeyAt(int index) const
{
    if (index < 0 || index >= Size())
    {
        throw runtime_error("Index out of bounds");
    }

    typename map<K, V>::const_iterator it = m_data.begin();
    for (int i = 0; i < index; i++)
    {
        ++it;
    }
    return it->first;
}

template <class K, class V>
V& Map<K, V>::ValueAt(int index)
{
    if (index < 0 || index >= Size())
    {
        throw runtime_error("Index out of bounds");
    }

    typename map<K, V>::iterator it = m_data.begin();
    for (int i = 0; i < index; i++)
    {
        ++it;
    }
    return it->second;
}

template <class K, class V>
const V& Map<K, V>::ValueAt(int index) const
{
    if (index < 0 || index >= Size())
    {
        throw runtime_error("Index out of bounds");
    }

    typename map<K, V>::const_iterator it = m_data.begin();
    for (int i = 0; i < index; i++)
    {
        ++it;
    }
    return it->second;
}

template <class K, class V>
void Map<K, V>::GetKeys(Vector<K>& out) const
{
    out.Clear();
    typename map<K, V>::const_iterator it = m_data.begin();
    while (it != m_data.end())
    {
        out.Add(it->first);
        ++it;
    }
}

#endif // MAP_H_INCLUDED
