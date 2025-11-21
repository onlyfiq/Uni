#include <iostream>
#include <cassert>
#include "DateTimeKey.h"
#include "Date.h"
#include "Time.h"

using namespace std;

void TestEquality()
{
    Date d1(10, 5, 2024);
    Time t1(14, 30);

    DateTimeKey a(d1, t1);
    DateTimeKey b(d1, t1);

    assert(a == b);
    assert(!(a < b));
    assert(!(a > b));

    cout << "Equality test OK\n";
}

void TestOrdering()
{
    DateTimeKey k1(Date(1, 1, 2023), Time(0, 0));
    DateTimeKey k2(Date(1, 1, 2024), Time(0, 0));

    assert(k1 < k2);
    assert(k2 > k1);

    cout << "Year ordering OK\n";

    DateTimeKey m1(Date(1, 1, 2024), Time(0, 0));
    DateTimeKey m2(Date(1, 2, 2024), Time(0, 0));

    assert(m1 < m2);

    cout << "Month ordering OK\n";

    DateTimeKey d1(Date(10, 2, 2024), Time(0, 0));
    DateTimeKey d2(Date(11, 2, 2024), Time(0, 0));

    assert(d1 < d2);

    cout << "Day ordering OK\n";

    DateTimeKey h1(Date(10, 2, 2024), Time(12, 0));
    DateTimeKey h2(Date(10, 2, 2024), Time(13, 0));

    assert(h1 < h2);

    cout << "Hour ordering OK\n";

    DateTimeKey min1(Date(10, 2, 2024), Time(12, 10));
    DateTimeKey min2(Date(10, 2, 2024), Time(12, 20));

    assert(min1 < min2);

    cout << "Minute ordering OK\n";
}

int main()
{
    TestEquality();
    TestOrdering();

    cout << "All DateTimeKey tests passed.\n";
    return 0;
}
