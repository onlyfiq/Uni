#ifndef ENCAPVECT_H_INCLUDED
#define ENCAPVECT_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <vector>

using std::out_of_range;
using std::vector;

/**
 * @class Vector
 * @brief A simplified wrapper around std::vector providing controlled access and basic operations.
 *
 * This templated Vector class supports dynamic resizing, element insertion,
 * deletion, indexed access with bounds checking, and size queries.
 * It is intentionally limited compared to std::vector to align with unit-testing
 * and teaching requirements of the assignment.
 *
 * @tparam T Type of elements stored in the vector.
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Constructs an empty Vector.
     */
    Vector();

    /**
     * @brief Constructs a Vector with a preallocated size.
     * @param n Number of elements to allocate. Values are default-initialized.
     */
    Vector(int n);

    /**
     * @brief Appends a new value to the end of the vector.
     * @param value Element to append.
     * @return True if the operation succeeded, false if memory allocation failed.
     */
    bool Add(const T& value);

    /**
     * @brief Inserts an element at a given index.
     *
     * Elements at and after the index are shifted to the right.
     *
     * @param index Position to insert at (0 ≤ index ≤ size).
     * @param value Element to insert.
     * @return True if index was valid and insertion succeeded, otherwise false.
     */
    bool Insert(int index, const T& value);

    /**
     * @brief Deletes the element at a given index.
     * @param index Index of the element to remove.
     * @return True if deletion succeeded, false if index was invalid.
     */
    bool Delete(int index);

    /**
     * @brief Returns the number of elements currently stored.
     * @return Size of the vector.
     */
    int GetSize() const;

    /**
     * @brief Checks whether the vector is empty.
     * @return True if no elements exist, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * @brief Removes all elements from the vector.
     */
    void Clear();

    /**
     * @brief Appends an element to the end of the vector.
     *
     * Unlike Add(), this method assumes no allocation failure.
     *
     * @param value Element to append.
     */
    void PushBack(const T& value);

    /**
     * @brief Provides indexed access to elements with bounds checking.
     * @param index Index of the requested element.
     * @return Reference to the element at the specified index.
     * @throws out_of_range If index is invalid.
     */
    T& operator[](int index);

    /**
     * @brief Provides const indexed access to elements with bounds checking.
     * @param index Index of the requested element.
     * @return Const reference to the element at the specified index.
     * @throws out_of_range If index is invalid.
     */
    const T& operator[](int index) const;

private:
    vector<T> m_data; ///< Underlying storage container.
};


template <class T>
Vector<T>::Vector() : m_data()
{
}

template <class T>
Vector<T>::Vector(int n) : m_data()
{
    if (n > 0)
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
        return true;
    }
    catch (...)
    {
        return false;
    }
}

template <class T>
void Vector<T>::PushBack(const T& value)
{
    m_data.push_back(value);
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
        return true;
    }
    catch (...)
    {
        return false;
    }
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
    if (index < 0 || index >= m_data.size())
    {
        throw out_of_range("Index out of bounds");
    }
    return m_data[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= m_data.size())
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

template <class T>
bool Vector<T>::IsEmpty() const
{
    return m_data.empty();
}

template <class T>
void Vector<T>::Clear()
{
    m_data.clear();
}

#endif // ENCAPVECT_H_INCLUDED
