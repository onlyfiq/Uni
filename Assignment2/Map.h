#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <map>
#include <stdexcept>
#include "EncapVect.h"

using std::runtime_error;
using std::map;

/**
 * @class Map
 * @brief A lightweight wrapper around std::map providing simplified access methods.
 *
 * This templated Map class behaves similarly to std::map but exposes only the
 * features required by the assignment. It supports key lookup, element access,
 * size retrieval, clearing, and extracting all keys into a Vector container.
 *
 * @tparam K Type of the map keys.
 * @tparam V Type of the mapped values.
 */
template <class K, class V>
class Map
{
public:
    /**
     * @brief Default constructor. Creates an empty map.
     */
    Map();

    /**
     * @brief Checks whether a given key exists in the map.
     * @param key Key to search for.
     * @return True if the key is present, otherwise false.
     */
    bool Contains(const K& key) const;

    /**
     * @brief Returns the total number of key–value pairs stored.
     * @return Number of elements in the map.
     */
    int Size() const;

    /**
     * @brief Removes all elements from the map.
     */
    void Clear();

    /**
     * @brief Accesses (or creates) the value associated with a key.
     *
     * If the key does not exist, a default-initialized value is inserted.
     *
     * @param key Key whose associated value is being accessed.
     * @return Reference to the associated value.
     */
    V& operator[](const K& key);

    /**
     * @brief Retrieves the value for a key without inserting defaults.
     *
     * Throws a runtime_error if the key is not present.
     *
     * @param key Key whose associated value is requested.
     * @return Constant reference to the associated value.
     * @throws runtime_error If the key does not exist.
     */
    const V& At(const K& key) const;

    /**
     * @brief Retrieves all keys stored in the map.
     *
     * The keys are appended (in sorted order) to the given Vector.
     *
     * @param out Vector that will receive the keys.
     */
    void GetKeys(Vector<K>& out) const;

private:
    map<K, V> m_data; ///< Internal std::map holding all key–value pairs.
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
