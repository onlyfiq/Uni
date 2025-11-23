//#include "Vector.h"
// EncapVectTest.cpp
#include "EncapVect.h"
#include <iostream>

using namespace std;

// Global vector for testing
Vector<int> myVector;

// Test function prototypes
void DefaultTest();
void InsertTest();
void InsertInvalidTest();
void DeleteTest();
void DeleteInvalidTest();
void AccessTest();
void AccessInvalidTest();
void CopyTest();
void AssignTest();

int main()
{
    cout << "==== EncapVect / Vector Class Test ====" << endl << endl;

    DefaultTest();
    InsertTest();
    InsertInvalidTest();
    DeleteTest();
    DeleteInvalidTest();
    AccessTest();
    AccessInvalidTest();
    CopyTest();
    AssignTest();

    cout << "==== End of Vector Tests ====" << endl;
    return 0;
}

void DefaultTest()
{
    cout << "Test 1: Default Constructor" << endl;
    cout << "Expected size: 0 | Actual: " << myVector.GetSize() << endl << endl;
}

void InsertTest()
{
    cout << "Test 2: Insert Valid Elements" << endl;

    // Insert 1–5
    for(int i = 1; i <= 5; i++)
        myVector.Insert(myVector.GetSize(), i);

    cout << "Expected size: 5 | Actual: " << myVector.GetSize() << endl;

    cout << "Expected elements: 1 2 3 4 5 | Actual: ";
    for(int i = 0; i < myVector.GetSize(); i++)
        cout << myVector[i] << " ";
    cout << endl;

    // Insert 99 at index 1
    myVector.Insert(1, 99);
    cout << "After inserting 99 at index 1 (Expected: 1 99 2 3 4 5): ";

    for(int i = 0; i < myVector.GetSize(); i++)
        cout << myVector[i] << " ";

    cout << endl << endl;
}

void InsertInvalidTest()
{
    cout << "Test 3: Insert Invalid Index" << endl;

    // Negative index
    cout << "Insert at index -1 (should ignore or handle safely)" << endl;
    myVector.Insert(-1, 500);

    // Index > size
    cout << "Insert at index 999 (should append or ignore depending on your code)" << endl;
    myVector.Insert(999, 600);

    cout << "Vector after invalid inserts: ";
    for(int i = 0; i < myVector.GetSize(); i++)
        cout << myVector[i] << " ";

    cout << endl << endl;
}

void DeleteTest()
{
    cout << "Test 4: Delete Valid Index (delete index 0)" << endl;

    myVector.Delete(0);

    cout << "After deleting index 0: ";
    for(int i = 0; i < myVector.GetSize(); i++)
        cout << myVector[i] << " ";

    cout << endl << endl;
}

void DeleteInvalidTest()
{
    cout << "Test 5: Delete Invalid Index" << endl;

    // Negative index
    cout << "Attempt delete at -1" << endl;
    myVector.Delete(-1);

    // Too large index
    cout << "Attempt delete at 999" << endl;
    myVector.Delete(999);

    cout << "Vector after invalid delete attempts: ";
    for(int i = 0; i < myVector.GetSize(); i++)
        cout << myVector[i] << " ";

    cout << endl << endl;
}

void AccessTest()
{
    cout << "Test 6: Valid Access Operator []" << endl;

    cout << "Element at index 0 (Expected: first element): ";
    cout << myVector[0] << endl << endl;
}

void AccessInvalidTest()
{
    cout << "Test 7: Invalid Access (Out of Bounds)" << endl;

    cout << "Access index -1 (behavior depends on your operator[]): ";
    cout << myVector[0] << endl;

    cout << "Access index 999: ";
//    cout << myVector[999] << endl << endl;
}

void CopyTest()
{
    cout << "Test 8: Copy Constructor" << endl;

    Vector<int> copied(myVector);

    cout << "Copied vector elements: ";
    for(int i = 0; i < copied.GetSize(); i++)
        cout << copied[i] << " ";

    cout << endl << endl;
}

void AssignTest()
{
    cout << "Test 9: Assignment Operator" << endl;

    Vector<int> assigned;
    assigned = myVector;

    cout << "Assigned vector elements: ";
    for(int i = 0; i < assigned.GetSize(); i++)
        cout << assigned[i] << " ";

    cout << endl << endl;
}
