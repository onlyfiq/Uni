#ifndef RECNODE_H_INCLUDED
#define RECNODE_H_INCLUDED

#include "WeatherRec.h"
#include "DateTimeKey.h"

/**
 * @struct RecNode
 * @brief Node wrapper storing a WeatherRec and its sortable DateTimeKey for BST usage.
 *
 * RecNode acts as the element type stored in the binary search tree. Each node
 * contains a WeatherRec and an associated DateTimeKey that determines ordering
 * within the BST. Comparison operators use only the DateTimeKey, ensuring that
 * tree operations are based strictly on chronological order.
 */
struct RecNode
{
    DateTimeKey key;  /**< Chronological key generated from the record's date and time. */
    WeatherRec rec;   /**< Full weather record stored in this node. */

    /**
     * @brief Default constructor.
     *
     * Leaves members default-initialized. Intended mainly for container compatibility.
     */
    RecNode() = default;

    /**
     * @brief Constructs a RecNode from a WeatherRec.
     * @param w The WeatherRec from which to build this node.
     *
     * Generates a DateTimeKey using the record's date and time, ensuring that
     * RecNode objects can be placed in the BST in chronological order.
     */
    RecNode(const WeatherRec &w)
        : key(w.GetDate(), w.GetTime()), rec(w)
    {
    }

    /**
     * @brief Comparison operator for BST ordering.
     * @param other Another RecNode to compare against.
     * @return True if this node's key is earlier than the other's key.
     */
    bool operator<(const RecNode &other) const
    {
        return key < other.key;
    }

    /**
     * @brief Comparison operator for BST ordering.
     * @param other Another RecNode to compare against.
     * @return True if this node's key is later than the other's key.
     */
    bool operator>(const RecNode &other) const
    {
        return key > other.key;
    }

    /**
     * @brief Equality comparison based on the DateTimeKey.
     * @param other Another RecNode to compare against.
     * @return True if both nodes share the same DateTimeKey.
     */
    bool operator==(const RecNode &other) const
    {
        return key == other.key;
    }
};

#endif // RECNODE_H_INCLUDED
