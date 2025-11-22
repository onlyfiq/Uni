#include <iostream>
#include <cassert>
#include "DateTimeKey.h"
#include "Date.h"
#include "Time.h"

using namespace std;

// Test that identical DateTimeKey values
// compare equal and are not less/greater.
void TestEquality()
{
    Date d1(10, 5, 2024);
    Time t1(14, 30);

    // Create two identical keys
    DateTimeKey a(d1, t1);
    DateTimeKey b(d1, t1);

    // They should be equal
    assert(a == b);

    // Neither should be less or greater than the other
    assert(!(a < b));
    assert(!(a > b));

    cout << "Equality test OK\n";
}

// Test ordering across each field:
// year -> month -> day -> hour -> minute
// Ensures operator< and operator> behave correctly.
void TestOrdering()
{
    // Year comparison
    DateTimeKey k1(Date(1, 1, 2023), Time(0, 0));
    DateTimeKey k2(Date(1, 1, 2024), Time(0, 0));

    assert(k1 < k2);
    assert(k2 > k1);

    cout << "Year ordering OK\n";

    // Month comparison
    DateTimeKey m1(Date(1, 1, 2024), Time(0, 0));
    DateTimeKey m2(Date(1, 2, 2024), Time(0, 0));

    assert(m1 < m2);

    cout << "Month ordering OK\n";

    // Day comparison
    DateTimeKey d1(Date(10, 2, 2024), Time(0, 0));
    DateTimeKey d2(Date(11, 2, 2024), Time(0, 0));

    assert(d1 < d2);

    cout << "Day ordering OK\n";

    // Hour comparison
    DateTimeKey h1(Date(10, 2, 2024), Time(12, 0));
    DateTimeKey h2(Date(10, 2, 2024), Time(13, 0));

    assert(h1 < h2);

    cout << "Hour ordering OK\n";

    // Minute comparison
    DateTimeKey min1(Date(10, 2, 2024), Time(12, 10));
    DateTimeKey min2(Date(10, 2, 2024), Time(12, 20));

    assert(min1 < min2);

    cout << "Minute ordering OK\n";
}

// Program entry point for running tests
int main()
{
    // Run all test groups
    TestEquality();
    TestOrdering();

    cout << "All DateTimeKey tests passed.\n";
    return 0;
}
