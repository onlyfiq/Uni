#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <stdexcept>

using std::out_of_range;

const int INITIAL_CAPACITY = 10;

/**
 * @brief A template class that implements a dynamic array (vector)
 *
 * @tparam T Type of elements stored in the vector
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Default constructor
     * Initializes the vector with an initial capacity.
     */
    Vector();

    /**
     * @brief Parameterized constructor
     * @param n Initial capacity of the vector
     */
    Vector(int n);

    /**
     * @brief Copy constructor
     * @param other Vector to copy from
     */
    Vector(const Vector<T>& other);

    /**
     * @brief Destructor
     * Frees dynamically allocated memory.
     */
    ~Vector();

    /**
     * @brief Assignment operator
     * @param other Vector to assign from
     * @return Reference to this vector
     */
    Vector<T>& operator=(const Vector<T>& other);

    /**
     * @brief Inserts a value at a given index
     * @param index Position to insert at (0-based)
     * @param value Value to insert
     * @return true if insertion succeeded, false if index invalid
     */
    bool Insert(int index, const T& value);

    /**
     * @brief Deletes the element at a given index
     * @param index Position to delete (0-based)
     * @return true if deletion succeeded, false if index invalid
     */
    bool Delete(int index);

    /**
     * @brief Returns the number of elements in the vector
     * @return Current size of the vector
     */
    int GetSize() const;

    /**
     * @brief Access element at a given index
     * @param index Position of the element
     * @return Reference to element at index
     * @throws out_of_range if index is invalid
     */
    T& operator[](int index);

    /**
     * @brief Access element at a given index (const version)
     * @param index Position of the element
     * @return Const reference to element at index
     * @throws out_of_range if index is invalid
     */
    const T& operator[](int index) const;

private:
    T* m_array;        /**< Pointer to dynamic array */
    int m_size;        /**< Number of elements stored */
    int m_capacity;    /**< Allocated capacity */

    /**
     * @brief Resizes the vector if it is more than half full
     */
    void Resize();
};

template <class T>
Vector<T>::Vector()
{
    m_capacity = INITIAL_CAPACITY;
    m_array = new T[m_capacity];
    m_size = 0;
}

template <class T>
Vector<T>::Vector(int n)
{
    m_capacity = (n > 0) ? n : INITIAL_CAPACITY;
    m_array = new T[m_capacity];
    m_size = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    if(m_capacity > 0)
    {
        m_array = new T[m_capacity];
        for(int i = 0; i < m_size; i++)
        {
            m_array[i] = other.m_array[i];
        }
    }
    else
        m_array = nullptr;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] m_array;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if(this == &other)
    {
        return *this;
    }

    delete[] m_array;

    m_size = other.m_size;
    m_capacity = other.m_capacity;

    if(m_capacity > 0)
    {
        m_array = new T[m_capacity];
        for(int i = 0; i < m_size; i++)
        {
            m_array[i] = other.m_array[i];
        }
    }
    else
    {
        m_array = nullptr;
    }

    return *this;
}

template <class T>
void Vector<T>::Resize()
{
    if(m_size > m_capacity / 2)
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* newArray = new T[newCapacity];
        for(int i = 0; i < m_size; i++)
        {
            newArray[i] = m_array[i];
        }
        delete[] m_array;
        m_array = nullptr;
        m_array = newArray;
        m_capacity = newCapacity;
    }
}

template <class T>
bool Vector<T>::Insert(int index, const T& value)
{
    if(index < 0 || index > m_size)
    {
        return false;
    }

    Resize();
    for(int i = m_size - 1; i >= index; i--)
    {
        m_array[i + 1] = m_array[i];
    }

    m_array[index] = value;
    m_size++;
    return true;
}

template <class T>
bool Vector<T>::Delete(int index)
{
    if(index < 0 || index >= m_size)
    {
        return false;
    }

    for(int i = index; i < m_size - 1; i++)
    {
        m_array[i] = m_array[i + 1];
    }

    m_size--;
    return true;
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if(index < 0 || index >= m_size)
    {
        throw out_of_range("Index out of bounds");
    }
    return m_array[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if(index < 0 || index >= m_size)
    {
        throw out_of_range("Index out of bounds");
    }
    return m_array[index];
}

template <class T>
int Vector<T>::GetSize() const
{
    return m_size;
}

#endif // VECTOR_H_INCLUDED
