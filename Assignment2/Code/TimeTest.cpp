#include "Time.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "==== Time Class Test ====" << endl << endl;

    // Default Construction
    cout << "Test 1: Default Constructor" << endl;
    Time t1;
    cout << "Expected: 00:00 | Actual: " << t1 << endl << endl;

    // Valid Parameterized Constructor
    cout << "Test 2: Parameterized Constructor (Valid)" << endl;
    Time t2(13, 45);
    cout << "Expected: 13:45 | Actual: " << t2 << endl;

    Time t3(5, 7);
    cout << "Expected: 05:07 | Actual: " << t3 << endl << endl;

    // Invalid Parameterized Constructor
    cout << "Test 3: Parameterized Constructor (Invalid)" << endl;
    Time t4(25, 10);  // Invalid hour
    cout << "Expected: 00:10 | Actual: " << t4 << endl;

    Time t5(10, 70);  // Invalid minutes
    cout << "Expected: 10:00 | Actual: " << t5 << endl;

    Time t6(-1, -5);  // Both invalid
    cout << "Expected: 00:00 | Actual: " << t6 << endl << endl;

    // SetTime() Valid
    cout << "Test 4: SetTime (Valid values)" << endl;
    Time t7;
    t7.SetTime(23, 59);
    cout << "Expected: 23:59 | Actual: " << t7 << endl;

    t7.SetTime(8, 30);
    cout << "Expected: 08:30 | Actual: " << t7 << endl << endl;

    // SetTime() Invalid
    cout << "Test 5: SetTime (Invalid values)" << endl;
    Time t8;
    t8.SetTime(24, 10); // Invalid hour
    cout << "Expected: 00:10 | Actual: " << t8 << endl;

    t8.SetTime(15, 75); // Invalid minutes
    cout << "Expected: 15:00 | Actual: " << t8 << endl;

    t8.SetTime(-9, -9); // Both invalid
    cout << "Expected: 00:00 | Actual: " << t8 << endl << endl;

    // GetHours / GetMinutes
    cout << "Test 6: GetHours() and GetMinutes()" << endl;
    Time t9(16, 20);
    cout << "Hours Expected: 16 | Actual: " << t9.GetHours() << endl;
    cout << "Minutes Expected: 20 | Actual: " << t9.GetMinutes() << endl << endl;

    // Input Operator >>
    cout << "Test 7: Input Operator >>" << endl;
    Time t10;

    cout << "Enter time in HH:MM format (e.g. 09:15): ";
    cin >> t10;
    cout << "You entered: " << t10 << endl << endl;

    // Output Operator <<
    cout << "Test 8: Output Operator <<" << endl;
    Time t11(4, 9);
    cout << "Expected: 04:09 | Actual: " << t11 << endl;

    Time t12(12, 30);
    cout << "Expected: 12:30 | Actual: " << t12 << endl << endl;

    cout << "==== End of Time Class Tests ====" << endl;

    return 0;
}
