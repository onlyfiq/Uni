#ifndef RECNODE_H_INCLUDED
#define RECNODE_H_INCLUDED

#include "WeatherRec.h"
#include "DateTimeKey.h"

/**
 * @struct RecNode
 * @brief Wrapper for storing WeatherRec with a sortable key in BST.
 */
struct RecNode
{
    DateTimeKey key;
    WeatherRec rec;

    RecNode() = default;

    RecNode(const WeatherRec &w)
        : key(w.GetDate(), w.GetTime()), rec(w)
    {
    }

    bool operator<(const RecNode &other) const
    {
        return key < other.key;
    }

    bool operator>(const RecNode &other) const
    {
        return key > other.key;
    }

    bool operator==(const RecNode &other) const
    {
        return key == other.key;
    }
};

#endif // RECNODE_H_INCLUDED
