//#include "Vector.h"
#include "EncapVect.h"
#include <iostream>

using namespace std;

Vector<int> myVector;

void DefaultTest();
void InsertTest();
void DeleteTest();
void AccessTest();
void CopyTest();
void AssignTest();

int main()
{
    DefaultTest();
    InsertTest();
    DeleteTest();
    AccessTest();
    CopyTest();
    AssignTest();

    return 0;
}

void DefaultTest()
{
    cout << "Default Constructor, initial size: " << myVector.GetSize() << endl << endl;
}

void InsertTest()
{
    cout << "Insert test" << endl;
    // Add elements using Insert at the end
    myVector.Insert(myVector.GetSize(), 1);
    myVector.Insert(myVector.GetSize(), 2);
    myVector.Insert(myVector.GetSize(), 3);
    myVector.Insert(myVector.GetSize(), 4);
    myVector.Insert(myVector.GetSize(), 5);

    cout << "Size after inserting: " << myVector.GetSize() << endl;
    cout << "Elements: ";
    for(int i = 0; i < myVector.GetSize(); i++)
    {
        cout << myVector[i] << " ";
    }
    cout << endl;

    // Insert 99 at index 1
    myVector.Insert(1, 99);
    cout << "After inserting 99 at index 1: ";
    for(int i = 0; i < myVector.GetSize(); i++)
    {
        cout << myVector[i] << " ";
    }
    cout << endl << endl;
}

void DeleteTest()
{
    cout << "Delete test" << endl;
    myVector.Delete(0); // Delete element at index 0
    cout << "After deleting index 0: ";
    for(int i = 0; i < myVector.GetSize(); i++)
    {
        cout << myVector[i] << " ";
    }
    cout << endl << endl;
}

void AccessTest()
{
    cout << "Access operator test" << endl;
    cout << "Element at index 0: " << myVector[0] << endl << endl;
}

void CopyTest()
{
    cout << "Copy constructor test" << endl;
    Vector<int> copiedVector(myVector);
    cout << "Copied vector elements: ";
    for(int i = 0; i < copiedVector.GetSize(); i++)
    {
        cout << copiedVector[i] << " ";
    }
    cout << endl << endl;
}

void AssignTest()
{
    cout << "Assignment operator test" << endl;
    Vector<int> assignedVector;
    assignedVector = myVector;
    cout << "Assigned vector elements: ";
    for(int i = 0; i < assignedVector.GetSize(); i++)
    {
        cout << assignedVector[i] << " ";
    }
    cout << endl << endl;
}
