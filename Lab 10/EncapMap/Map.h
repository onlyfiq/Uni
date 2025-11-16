#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <map>

//using namespace std;
using std::map;
using std::runtime_error;
using std::cout;
using std::endl;

template <typename K, typename V>
class Map
{
public:
    // Add or update a key-value pair
    void AddOrUpdate(const K& key, const V& value)
    {
        data[key] = value;
    }

    // Remove an entry by key
    void Remove(const K& key)
    {
        data.erase(key);
    }

    // Check if a key exists
    bool Contains(const K& key) const
    {
        return data.find(key) != data.end();
    }

    // Retrieve a value by key
    V Get(const K& key) const
    {
        auto it = data.find(key);
        if (it != data.end())
            return it->second;
        throw runtime_error("Key not found");
    }

    // Print all entries
    void DisplayAll() const
    {
        cout << "Map Contents:\n";
        for (auto const& [key, value] : data)
        {
            cout << key << " -> " << value << endl;
        }
    }

    // Get size of map
    size_t Size() const
    {
        return data.size();
    }

    // Clear all entries
    void Clear()
    {
        data.clear();
    }

private:
    map<K, V> data; // STL map for storage

};

#endif // MAP_H_INCLUDED
