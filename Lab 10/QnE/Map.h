#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <map>
#include <stdexcept>

/**
 * @brief A template class that wraps std::map to provide key-value storage
 *
 * @tparam K Type of keys
 * @tparam V Type of values
 */
template <class K, class V>
class Map
{
public:
    /**
     * @brief Default constructor
     * Initializes an empty map.
     */
    Map();

    /**
     * @brief Add a key-value pair or update the value if the key exists
     * @param key Key to insert/update
     * @param value Value to assign
     */
    void AddOrUpdate(const K& key, const V& value);

    /**
     * @brief Remove an element by key
     * @param key Key to remove
     */
    void Remove(const K& key);

    /**
     * @brief Check whether a key exists in the map
     * @param key Key to check
     * @return true if key found, else false
     */
    bool Contains(const K& key) const;

    /**
     * @brief Retrieve a value by key (returns a COPY)
     * @param key Key to find
     * @return Copy of stored value
     * @throws std::runtime_error if key not found
     */
    V Get(const K& key) const;

    /**
     * @brief Retrieve a modifiable reference to a value
     * @param key Key to find
     * @return Reference to stored value
     * @throws std::runtime_error if key not found
     */
    V& GetRef(const K& key);

    /**
     * @brief Retrieve a const reference to a value
     * @param key Key to find
     * @return Const reference to stored value
     * @throws std::runtime_error if key not found
     */
    const V& GetConst(const K& key) const;

    /**
     * @brief Fill a vector-like container with all keys in sorted order
     * @tparam VecType A vector class supporting Clear() and Add()
     * @param keys Output vector of keys
     */
    template <class VecType>
    void FillKeys(VecType& keys) const;

    /**
     * @brief Print all key-value pairs (debug function)
     */
    void DisplayAll() const;

    /**
     * @brief Get the number of entries in the map
     * @return Map size
     */
    int Size() const;

    /**
     * @brief Remove all entries from the map
     */
    void Clear();

private:
    std::map<K, V> m_data;   /**< Internal storage (balanced BST) */
};

template <class K, class V>
Map<K, V>::Map()
{
    // std::map initializes itself
}

template <class K, class V>
void Map<K, V>::AddOrUpdate(const K& key, const V& value)
{
    m_data[key] = value;
}

template <class K, class V>
void Map<K, V>::Remove(const K& key)
{
    m_data.erase(key);
}

template <class K, class V>
bool Map<K, V>::Contains(const K& key) const
{
    return m_data.find(key) != m_data.end();
}

template <class K, class V>
V Map<K, V>::Get(const K& key) const
{
    typename std::map<K, V>::const_iterator it = m_data.find(key);

    if(it != m_data.end())
    {
        return it->second;
    }
    throw std::runtime_error("Key not found");
}

template <class K, class V>
V& Map<K, V>::GetRef(const K& key)
{
    typename std::map<K, V>::iterator it = m_data.find(key);

    if(it == m_data.end())
    {
        throw std::runtime_error("Key not found");
    }
    return it->second;
}

template <class K, class V>
const V& Map<K, V>::GetConst(const K& key) const
{
    typename std::map<K, V>::const_iterator it = m_data.find(key);

    if(it == m_data.end())
    {
        throw std::runtime_error("Key not found");
    }
    return it->second;
}

template <class K, class V>
template <class VecType>
void Map<K, V>::FillKeys(VecType& keys) const
{
    keys.Clear();

    typename std::map<K, V>::const_iterator it;
    for(it = m_data.begin(); it != m_data.end(); ++it)
    {
        keys.Add(it->first);
    }
}

template <class K, class V>
void Map<K, V>::DisplayAll() const
{
    typename std::map<K, V>::const_iterator it;

    std::cout << "Map Contents:\n";
    for(it = m_data.begin(); it != m_data.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
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

#endif // MAP_H_INCLUDED
