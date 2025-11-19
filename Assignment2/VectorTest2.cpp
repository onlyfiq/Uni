#include "Vector.h"
#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

// Forward declarations of test routines
int testIntVec(Vector<int> &vec);
int testDateVecValue(Vector<Date> vec);      // pass by value
int testDateVecRef(Vector<Date> &vec);       // pass by reference

// Template function to print a Vector (const reference)
template <typename T>
void printVec(const Vector<T>& vec, const string& name)
{
    cout << "Contents of " << name << " (size: " << vec.GetSize() << "):" << endl;
    for (int i = 0; i < vec.GetSize(); ++i)
    {
        cout << "  [" << i << "] " << vec[i] << endl;
    }
    cout << endl;
}

int main()
{
    Vector<int> intVec;
    Vector<Date> dateVec;

    // Run tests
    testIntVec(intVec);
    testDateVecValue(dateVec);   // pass by value (copy)
    testDateVecRef(dateVec);     // pass by reference (same object)

    return 0;
}

int testIntVec(Vector<int> &vec)
{
    cout << "\nInteger Vector Test" << endl;

    // Insert elements at the end
    for (int i = 1; i <= 5; i++)
    {
        vec.Insert(vec.GetSize(), i);
    }

    printVec(vec, "intVec after Insert");

    // Delete first element
    vec.Delete(0);
    printVec(vec, "intVec after Delete index 0");

    // Access operator
    cout << "Element at index 1: " << vec[1] << endl;

    // Copy constructor
    Vector<int> copyVec(vec);
    printVec(copyVec, "copyVec");

    // Assignment operator
    Vector<int> assignedVec;
    assignedVec = vec;
    printVec(assignedVec, "assignedVec");

    return 0;
}

int testDateVecValue(Vector<Date> vec) // pass by value
{
    cout << "\nDate Vector Test (by value)" << endl;

    vec.Insert(vec.GetSize(), Date(1, 1, 2025));
    vec.Insert(vec.GetSize(), Date(15, 3, 2025));
    vec.Insert(vec.GetSize(), Date(31, 12, 2025));

    printVec(vec, "dateVec (by value)");

    // Delete one element
    vec.Delete(1);
    printVec(vec, "dateVec after Delete index 1");

    cout << "Element at index 0: " << vec[0] << endl;

    return 0;
}

int testDateVecRef(Vector<Date> &vec) // pass by reference
{
    cout << "\nDate Vector Test (by reference)" << endl;

    vec.Insert(vec.GetSize(), Date(2, 2, 2025));
    vec.Insert(vec.GetSize(), Date(3, 3, 2025));

    printVec(vec, "dateVec (by reference)");

    vec.Delete(0); // delete first element
    printVec(vec, "dateVec after Delete index 0");

    cout << "Element at index 0: " << vec[0] << endl;

    return 0;
}
