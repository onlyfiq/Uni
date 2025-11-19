#include "Map.h"

int main()
{
    // Example 1: int -> double (Student results)
    Map<int, double> studentResults;
    studentResults.AddOrUpdate(101, 88.5);
    studentResults.AddOrUpdate(102, 93.0);
    studentResults.AddOrUpdate(103, 75.5);
    studentResults.DisplayAll();

    cout << "\nContains 102? " << (studentResults.Contains(102) ? "Yes" : "No") << endl;
    cout << "Result of 103 = " << studentResults.Get(103) << endl;

    // Example 2: string -> string (Usernames to passwords)
    Map<string, string> userAccounts;
    userAccounts.AddOrUpdate("alice", "password123");
    userAccounts.AddOrUpdate("bob", "hunter2");
    userAccounts.AddOrUpdate("charlie", "letmein");
    userAccounts.DisplayAll();

    // Example 3: string -> int (Words to frequency)
    Map<string, int> wordCount;
    wordCount.AddOrUpdate("hello", 3);
    wordCount.AddOrUpdate("world", 7);
    wordCount.AddOrUpdate("hello", 4); // update
    wordCount.DisplayAll();

    return 0;
}
