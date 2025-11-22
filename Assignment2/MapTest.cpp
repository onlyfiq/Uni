#include <iostream>
#include <string>
#include "Map.h"
using namespace std;

template <typename K, typename V>
void PrintMap(const Map<K,V>& m)
{
    Vector<K> keys;
    m.GetKeys(keys);

    for (int i = 0; i < keys.GetSize(); i++)
    {
        const K& key = keys[i];
        cout << "Key: " << key
             << "  Value: " << m.At(key) << endl;
    }
}

int main()
{
    cout << "=== TEST 1: int -> double (Student results) ===\n";
    Map<int, double> studentResults;

    // Insert using operator[]
    studentResults[101] = 88.5;
    studentResults[102] = 93.0;
    studentResults[103] = 75.5;

    PrintMap(studentResults);

    cout << "\nContains 102? "
         << (studentResults.Contains(102) ? "Yes" : "No") << endl;

    cout << "At(103) = " << studentResults.At(103) << endl;


    cout << "\n=== TEST 2: string -> string (User accounts) ===\n";
    Map<string, string> userAccounts;

    userAccounts["alice"]   = "password123";
    userAccounts["bob"]     = "hunter2";
    userAccounts["charlie"] = "letmein";

    PrintMap(userAccounts);


    cout << "\n=== TEST 3: string -> int (Word count) ===\n";
    Map<string, int> wordCount;

    wordCount["hello"] = 3;
    wordCount["world"] = 7;

    // Update test (operator[] overwrites existing)
    wordCount["hello"] = 4;

    PrintMap(wordCount);


    cout << "\n=== TEST 4: GetKeys() ===\n";
    Vector<string> keyList;
    wordCount.GetKeys(keyList);

    for (int i = 0; i < keyList.GetSize(); i++)
    {
        cout << "Key[" << i << "]: " << keyList[i] << endl;
    }


    cout << "\n=== TEST 5: Clear() ===\n";
    wordCount.Clear();

    cout << "Size after Clear(): " << wordCount.Size() << endl;
    cout << "Contains(\"hello\")? "
         << (wordCount.Contains("hello") ? "Yes" : "No") << endl;

    return 0;
}
