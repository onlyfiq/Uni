// Map.cpp
#include <iostream>
#include <string>
#include "Map.h"
using namespace std;

int main()
{
    cout << "=== TEST 1: int -> double (Student results) ===\n";
    Map<int, double> studentResults;

    // Insert using operator[]
    studentResults[101] = 88.5;
    studentResults[102] = 93.0;
    studentResults[103] = 75.5;

    // Display using KeyAt and ValueAt
    for (int i = 0; i < studentResults.Size(); i++)
    {
        cout << "Key: " << studentResults.KeyAt(i)
             << "  Value: " << studentResults.ValueAt(i) << endl;
    }

    cout << "\nContains 102? " << (studentResults.Contains(102) ? "Yes" : "No") << endl;
    cout << "At(103) = " << studentResults.At(103) << endl;


    cout << "\n=== TEST 2: string -> string (User accounts) ===\n";
    Map<string, string> userAccounts;

    userAccounts["alice"] = "password123";
    userAccounts["bob"]   = "hunter2";
    userAccounts["charlie"] = "letmein";

    for (int i = 0; i < userAccounts.Size(); i++)
    {
        cout << "Key: " << userAccounts.KeyAt(i)
             << "  Value: " << userAccounts.ValueAt(i) << endl;
    }


    cout << "\n=== TEST 3: string -> int (Word count) ===\n";
    Map<string, int> wordCount;

    wordCount["hello"] = 3;
    wordCount["world"] = 7;

    // Update test (operator[] changes existing)
    wordCount["hello"] = 4;

    for (int i = 0; i < wordCount.Size(); i++)
    {
        cout << "Key: " << wordCount.KeyAt(i)
             << "  Value: " << wordCount.ValueAt(i) << endl;
    }


    cout << "\n=== TEST 4: GetKeys() ===\n";
    Vector<string> keyList;
    wordCount.GetKeys(keyList);

    for (int i = 0; i < keyList.GetSize(); i++)
    {
        cout << "Key[" << i << "]: " << keyList[i] << endl;
    }

    return 0;
}
